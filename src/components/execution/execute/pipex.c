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

static void	handle_child_process(t_cmd *cmd, char **envp, t_pipex_data *data, \
		int *exit_status)
{
	t_env	*env;

	if (handle_file_redirection(cmd, &data->infile, &data->outfile) == -1)
		return ;
	handle_redirection(data);
	if (cmd->type == COMMAND)
	{
		data->f_fd = 0;
		if (ft_execute_builtins(cmd->cmd, &env, exit_status, data) == SUCCESS)
		{
			close(data->pipe_fd[0]);
			close(data->pipe_fd[1]);
			close(data->prev_pipe_read);
			cleanup_child_fds(data);
			exit(0);
		}
		execute_cmd(cmd->cmd, envp, exit_status);
	}
	cleanup_child_fds(data);
	exit(1);
}

static void	process_command(t_cmd *cmd, char **envp, t_pipex_data *data, \
		int *exit_status)
{
	pid_t	pid;

	if (data->current_cmd < data->cmd_count - 1)
	{
		if (pipe(data->pipe_fd) == -1)
			error_and_exit("Pipe creation failed", 1);
	}
	pid = fork();
	if (pid == 0)
		handle_child_process(cmd, envp, data, exit_status);
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

static void	process_commands_loop(t_cmd *cmd, char **envp, \
	t_pipex_data *data, int *exit_status)
{
	while (cmd)
	{
		process_command(cmd, envp, data, exit_status);
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
	char			**envp;

	cmd = commands;
	init_pipex_data(&data, commands);
	envp = ft_env_create_2d(*env);
	process_commands_loop(cmd, envp, &data, exit_status);
	wait_for_children(data.cmd_count, exit_status);
	cleanup_child_fds(&data);
}
