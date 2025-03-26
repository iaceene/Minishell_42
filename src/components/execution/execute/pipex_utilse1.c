/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilse1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:24:36 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/18 06:24:36 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

int	count_commands(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		if (cmd->type == COMMAND)
			count++;
		cmd = cmd->next;
	}
	return (count);
}

void	cleanup_child_fds(t_pipex_data *data)
{
	if (data->infile != -1 && data->infile != STDIN_FILENO)
		close(data->infile);
	if (data->outfile != -1 && data->outfile != STDOUT_FILENO)
		close(data->outfile);
	if (data->pipe_fd[0] != -1 && data->pipe_fd[0] != STDIN_FILENO)
		close(data->pipe_fd[0]);
	if (data->pipe_fd[1] != -1 && data->pipe_fd[1] != STDOUT_FILENO)
		close(data->pipe_fd[1]);
	if (data->prev_pipe_read != -1 && data->prev_pipe_read != STDIN_FILENO)
		close(data->prev_pipe_read);
}

void	handle_redirection(t_pipex_data *data)
{
	if (data->infile != -1)
	{
		if (dup2(data->infile, STDIN_FILENO) == -1)
			perror("dup2 infile");
		close(data->infile);
	}
	else if (data->current_cmd > 0 && data->prev_pipe_read != -1)
	{
		if (dup2(data->prev_pipe_read, STDIN_FILENO) == -1)
			perror("dup2 pipe read");
		close(data->prev_pipe_read);
	}
	if (data->outfile != -1)
	{
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
			perror("dup2 outfile");
		close(data->outfile);
	}
	else if (data->current_cmd < data->cmd_count - 1 && data->pipe_fd[1] != -1)
	{
		if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
			perror("dup2 pipe write");
		close(data->pipe_fd[1]);
	}
}

void	init_pipex_data(t_pipex_data *data, t_cmd *commands)
{
	data->infile = -1;
	data->outfile = -1;
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->prev_pipe_read = -1;
	data->cmd_count = count_commands(commands);
	data->current_cmd = 0;
}
