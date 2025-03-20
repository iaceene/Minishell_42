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

#include "../../../../include/minishell.h"

void	handle_child_process(t_exec *cmd, char **envp, t_pipex_data *data, \
	int *exit_status)
{
	handle_file_redirection(cmd, &data->infile, &data->outfile, data);
	handle_redirection(data);
	cleanup_child_fds(data);
	execute_cmd(cmd->s, envp, exit_status);
	exit(1);
}

void	process_command(t_exec *cmd, char **envp, t_pipex_data *data, \
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
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		handle_child_process(cmd, envp, data, exit_status);
	}
	else if (pid < 0)
	{
		perror(":");
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

void	close_fds(t_pipex_data *data)
{
	if (data->infile != -1)
		close(data->infile);
	if (data->outfile != -1)
		close(data->outfile);
	if (data->prev_pipe_read != -1)
		close(data->prev_pipe_read);
}

void	ft_pipex(t_exec *commands, t_env **env, int *exit_status)
{
	t_pipex_data	data;
	char			**envp;
	t_exec			*cmd;

	cmd = commands;
	if (ft_execute_builtins(&(cmd->value), env, exit_status) == SUCCESS)
	{
		*exit_status = 0;
		return ;
	}
	data = (t_pipex_data){-1, -1, {-1, -1}, -1, count_commands(commands), 0};
	envp = ft_env_create_2d(*env);
	cmd = commands;
	while (cmd)
	{
		if (cmd->type == COMMAND)
		{
			process_command(cmd, envp, &data, exit_status);
			data.current_cmd++;
		}
		cmd = cmd->next;
	}
	close_fds(&data);
	wait_for_children(data.cmd_count, exit_status);
}
