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



void	close_all_pipe(int **pipes, int num_cmd)
{
	int	j;

	if (!pipes)
		return ;
	j = 0;
	while (j < num_cmd - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	redirect_fd(int from_fd, int to_fd, const char *error_msg)
{
	if (from_fd < 0 || to_fd < 0)
		error_and_exit((char *)error_msg, 1);
	if (dup2(from_fd, to_fd) == -1)
		error_and_exit((char *)error_msg, 1);
	close(from_fd);
}

int	count_commands(t_exec *cmd)
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

void	cleanup_child_fds(int infile, int outfile, int pipe_read, int pipe_write, int prev_pipe)
{
	if (infile != -1 && infile != STDIN_FILENO)
		close(infile);
	if (outfile != -1 && outfile != STDOUT_FILENO)
		close(outfile);
	if (pipe_read != -1 && pipe_read != STDIN_FILENO)
		close(pipe_read);
	if (pipe_write != -1 && pipe_write != STDOUT_FILENO)
		close(pipe_write);
	if (prev_pipe != -1 && prev_pipe != STDIN_FILENO)
		close(prev_pipe);
}

void execute_command(t_exec *cmd, char **env)
{
	execute_cmd(cmd->s, env);
}
/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void handle_redirection(t_pipex_data *data)
{
	if (data->current_cmd == 0 && data->infile != -1)
		redirect_fd(data->infile, STDIN_FILENO, "dup2 failed (stdin)");
	else if (data->current_cmd > 0)
		redirect_fd(data->prev_pipe_read, STDIN_FILENO, "dup2 failed (stdin)");

	if (data->current_cmd == data->cmd_count - 1 && data->outfile != -1)
		redirect_fd(data->outfile, STDOUT_FILENO, "dup2 failed (stdout)");
	else if (data->current_cmd < data->cmd_count - 1)
		redirect_fd(data->pipe_fd[1], STDOUT_FILENO, "dup2 failed (stdout)");
}

void handle_child_process(t_exec *cmd, char **envp, t_pipex_data *data)
{
	
	handle_redirection(data);

	cleanup_child_fds(data->infile, data->outfile, data->pipe_fd[0], data->pipe_fd[1], data->prev_pipe_read);
	execute_command(cmd, envp);
	exit(1);
}

void process_command(t_exec *cmd, char **envp, t_pipex_data *data)
{
	pid_t pid;

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

void wait_for_children(int cmd_count, int *exit_status)
{
	int status, last_status = 0, i = 0;

	while (i < cmd_count)
	{
		wait(&status);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		i++;
	}
	*exit_status = last_status;
}

void ft_pipex(t_exec *commands, t_env **env, int *exit_status)
{
	t_pipex_data data = { -1, -1, {-1, -1}, -1, count_commands(commands), 0 };
	char **envp = ft_env_create_2d(*env);
	handle_file_redirection(commands, &data.infile, &data.outfile);

	t_exec *cmd = commands;

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
