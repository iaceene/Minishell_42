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

void redirect_fd(int from_fd, int to_fd, const char *error_msg)
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

void handle_redirection(t_pipex_data *data)
{
	if (data->current_cmd == 0 && data->infile != -1)
		redirect_fd(data->infile, STDIN_FILENO, "dup2 failed (stdin ho)");
	else if (data->current_cmd > 0)
		redirect_fd(data->prev_pipe_read, STDIN_FILENO, "dup2 failed (stdin hi)");

	if (data->current_cmd == data->cmd_count - 1 && data->outfile != -1)
		redirect_fd(data->outfile, STDOUT_FILENO, "dup2 failed (stdout)");
	else if (data->current_cmd < data->cmd_count - 1)
		redirect_fd(data->pipe_fd[1], STDOUT_FILENO, "dup2 failed (stdout)");
}

void handle_child_process(t_cmd *cmd, char **envp, t_pipex_data *data,
						  int *exit_status)
{
	t_env *env;
	if (handle_file_redirection(cmd, &data->infile, &data->outfile, data) == -1)
		return;
	handle_redirection(data);
	if (cmd->type == COMMAND)
	{
		if (ft_execute_builtins(cmd->cmd, &env, exit_status, data, 0) == SUCCESS)
		{
			close(data->pipe_fd[0]);
			close(data->pipe_fd[1]);
			close(data->prev_pipe_read);
			cleanup_child_fds(data);
			exit(0);
		}
		// cleanup_child_fds(data);

		execute_cmd(cmd->cmd, envp, exit_status);
	}
	cleanup_child_fds(data);
	exit(1);
}

void process_command(t_cmd *cmd, char **envp, t_pipex_data *data,
					 int *exit_status)
{
	pid_t pid;

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

void wait_for_children(int cmd_count, int *exit_status)
{
	int status;
	int last_status;
	int i;

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

void close_fds(t_pipex_data *data)
{
	if (data->infile != -1)
		close(data->infile);
	if (data->outfile != -1)
		close(data->outfile);
	if (data->prev_pipe_read != -1)
		close(data->prev_pipe_read);
}

int is_pure_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp("pwd", cmd, ft_strlen(cmd)) && ft_strlen(cmd) == ft_strlen("pwd"))
		return (1);
	return (0);
}

void process_commands_loop(t_cmd *cmd, char **envp, t_pipex_data *data, int *exit_status)
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

void init_pipex_data(t_pipex_data *data, t_cmd *commands)
{
	data->infile = -1;
	data->outfile = -1;
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->prev_pipe_read = -1;
	data->cmd_count = count_commands(commands);
	data->current_cmd = 0;
}

void ft(t_cmd **head)
{
	t_cmd *tmp;
	t_cmd *last = NULL;
	t_cmd *first_cmd = NULL;

	if (!head || !*head || (*head)->type == COMMAND)
		return;

	tmp = *head;
	while (tmp && tmp->type != COMMAND)
	{
		last = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return;
	first_cmd = tmp;
	if (last)
	{
		last->next = first_cmd->next;
		first_cmd->next = *head;
		*head = first_cmd;
	}
}

void ft_pipex(t_cmd *commands, t_env **env, int *exit_status)
{
	t_pipex_data data;
	t_cmd *cmd;
	char **envp;

	cmd = commands;
	init_pipex_data(&data, commands);
	envp = ft_env_create_2d(*env);

	// ft(&cmd);
	process_commands_loop(cmd, envp, &data, exit_status);
	wait_for_children(data.cmd_count, exit_status);
	cleanup_child_fds(&data);
	close_fds(&data);
}
