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

static void	handle_child_process(t_cmd *cmd, t_pipex_data *data, \
		int *exit_status, t_env **env)
{
	char	**envp;

	(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
	envp = ft_env_create_2d(*env);
	data->status = 3;
	if (handle_file_redirection(cmd, &data->infile, &data->outfile, 1) == -1)
		(cleanup_child_fds(data), exit(1));
	handle_redirection(data);
	if (cmd->type == COMMAND)
	{
		data->f_fd = 0;
		if (ft_execute_builtins(cmd->cmd, env, exit_status, data) == SUCCESS)
			(cleanup_child_fds(data), exit(*exit_status));
		cleanup_child_fds(data);
		execute_cmd(cmd->cmd, envp, exit_status);
	}
	cleanup_child_fds(data);
	exit(1);
}

static void	process_command(t_cmd *cmd, t_pipex_data *data, \
		int *exit_status, t_env **env)
{
	pid_t	pid;

	if (data->current_cmd < data->cmd_count - 1)
	{
		if (pipe(data->pipe_fd) == -1)
			error_and_exit("Pipe creation failed", 1);
	}
	(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
	pid = fork();
	if (pid == 0)
		handle_child_process(cmd, data, exit_status, env);
	else if (pid < 0)
	{
		perror("Fork");
		cleanup_child_fds(data);
		exit(1);
	}
	if (data->prev_pipe_read != -1)
		close(data->prev_pipe_read);
	if (data->current_cmd < data->cmd_count - 1)
	{
		close(data->pipe_fd[1]);
		data->prev_pipe_read = data->pipe_fd[0];
	}
}

static void	wait_for_children(int cmd_count, int *exit_status)
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
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				(write(1, "\n", 1), last_status = 130);
			else if (WTERMSIG(status) == SIGQUIT)
				(write(1, "Quit: 3\n", 8), last_status = 131);
		}
		i++;
	}
	*exit_status = last_status;
}

static void	process_commands_loop(t_cmd *cmd, \
	t_pipex_data *data, int *exit_status, t_env **env)
{
	while (cmd)
	{
		process_command(cmd, data, exit_status, env);
		if (cmd->type == COMMAND)
			data->current_cmd++;
		cmd = cmd->next;
		while (cmd && cmd->type != COMMAND)
			cmd = cmd->next;
	}
}

void	ft_pipex(t_cmd *commands, t_env **env, int *exit_status)
{
	t_pipex_data	data;
	t_cmd			*cmd;

	cmd = commands;
	init_pipex_data(&data, commands);
	ft_sort(&cmd);
	process_commands_loop(cmd, &data, exit_status, env);
	wait_for_children(data.cmd_count, exit_status);
	cleanup_child_fds(&data);
}
