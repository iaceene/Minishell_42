/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:02:23 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/19 10:02:23 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

void	handle_child_process(t_exec *cmd, char **envp, t_pipex_data *data)
{
	handle_redirection(data);
	cleanup_child_fds(data);
	execute_cmd(cmd->s, envp);
	exit(1);
}

void	process_command(t_exec *cmd, char **envp, t_pipex_data *data)
{
	pid_t	pid;

	if (data->current_cmd < data->cmd_count - 1)
	{
		if (pipe(data->pipe_fd) == -1)
			error_and_exit("Pipe creation failed", 1);
	}
	pid = fork();
	if (pid == 0)
		handle_child_process(cmd, envp, data);
	else if (pid < 0)
		error_and_exit("Fork failed", 1);
	if (data->prev_pipe_read != -1)
		close(data->prev_pipe_read);
	if (data->current_cmd < data->cmd_count - 1)
	{
		close(data->pipe_fd[1]);
		data->prev_pipe_read = data->pipe_fd[0];
	}
}

void	wait_for_children(int cmd_count, int *exit_status)
{
	int	status;
	int	last_status;
	int	i;

	last_status = 0;
	i = 0;
	while (i < cmd_count)
	{
		wait(&status);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		i++;
	}
	*exit_status = last_status;
}

void	ft_pipex(t_exec *commands, t_env **env, int *exit_status)
{
	t_pipex_data	data;
	char			**envp;
	t_exec			*cmd;

	data = (t_pipex_data){-1, -1, {-1, -1}, -1, count_commands(commands), 0};
	envp = ft_env_create_2d(*env);
	handle_file_redirection(commands, &data.infile, &data.outfile);
	cmd = commands;
	while (cmd)
	{
		if (cmd->type == COMMAND)
		{
			process_command(cmd, envp, &data);
			data.current_cmd++;
		}
		cmd = cmd->next;
	}
	if (data.infile != -1)
		close(data.infile);
	if (data.outfile != -1)
		close(data.outfile);
	if (data.prev_pipe_read != -1)
		close(data.prev_pipe_read);
	wait_for_children(data.cmd_count, exit_status);
}
