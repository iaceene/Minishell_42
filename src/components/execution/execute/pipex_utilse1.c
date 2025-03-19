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

static void	redirect_fd(int from_fd, int to_fd, const char *error_msg)
{
	if (from_fd < 0 || to_fd < 0)
	{
		perror("Invalid file descriptor");
		error_and_exit((char *)error_msg, 1);
	}
	if (dup2(from_fd, to_fd) == -1)
	{
		perror("dup2 failed");
		error_and_exit((char *)error_msg, 1);
	}
	close(from_fd);
}

void	handle_redirection(t_pipex_data *data)
{
	if (data->current_cmd == 0 && data->infile != -1)
		redirect_fd(data->infile, STDIN_FILENO, "dup2 failed (stdin ho)");
	else if (data->current_cmd > 0)
		redirect_fd(data->prev_pipe_read, STDIN_FILENO, \
			"dup2 failed (stdin hi)");
	if (data->current_cmd == data->cmd_count - 1 && data->outfile != -1)
		redirect_fd(data->outfile, STDOUT_FILENO, "dup2 failed (stdout)");
	else if (data->current_cmd < data->cmd_count - 1)
		redirect_fd(data->pipe_fd[1], STDOUT_FILENO, "dup2 failed (stdout)");
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
