/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:52 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/27 13:03:10 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

static int	setup_output_input_redirection(int f_fd, t_pipex_data *data, \
	int *stdout_backup, int *stdin_backup)
{
	int	rest;

	rest = 0;
	if (f_fd == 1)
	{
		if (data->infile != -1)
		{
			*stdin_backup = dup(0);
			if (dup2(data->infile, STDIN_FILENO) == -1)
				return (perror("dup2 infile"), FAILED);
			(close(data->infile), data->infile = -1, rest = 1);
		}
		if (data->outfile != -1)
		{
			*stdout_backup = dup(1);
			if (dup2(data->outfile, STDOUT_FILENO) == -1)
				return (perror("dup2 outfile"), FAILED);
			(close(data->outfile), data->outfile = -1, rest = 2);
		}
	}
	return (rest);
}

static int	restore_redirections(int f_fd, int k, int stdin_backup, \
			int stdout_backup)
{
	if (f_fd)
	{
		if (k == 1)
		{
			if (dup2(stdin_backup, STDIN_FILENO) == -1)
				return (perror("dup2 infile"), FAILED);
			close(stdin_backup);
		}
		if (k == 2)
		{
			if (dup2(stdout_backup, STDOUT_FILENO) == -1)
				return (perror("dup2 outfile"), FAILED);
			close(stdout_backup);
		}
	}
	return (0);
}

static int	execute_builtin_command(char **arg, t_env **env, int *exit_status)
{
	if (arg[0] && !ft_strncmp("env", arg[0], ft_strlen(arg[0])) && \
		ft_strlen(arg[0]) == ft_strlen("env"))
		return (builtin_env(*env, arg, exit_status), SUCCESS);
	else if (!ft_strncmp("echo", arg[0], ft_strlen(arg[0])) && \
		ft_strlen(arg[0]) == ft_strlen("echo"))
		return (builtin_echo(arg), *exit_status = 0, SUCCESS);
	else if (!ft_strncmp("cd", arg[0], ft_strlen(arg[0])) && \
		ft_strlen(arg[0]) == ft_strlen("cd"))
		return (builtin_cd(arg, env, exit_status), SUCCESS);
	else if (!ft_strncmp("export", arg[0], ft_strlen(arg[0])) && \
		ft_strlen(arg[0]) == ft_strlen("export"))
		return (builtin_export(env, arg, exit_status), SUCCESS);
	else if (!ft_strncmp("pwd", arg[0], ft_strlen(arg[0])) && \
		ft_strlen(arg[0]) == ft_strlen("pwd"))
		return (builtin_pwd(), *exit_status = 0, SUCCESS);
	else if (!ft_strncmp("unset", arg[0], ft_strlen(arg[0])) && \
		ft_strlen(arg[0]) == ft_strlen("unset"))
		return (builtin_unset(env, arg, exit_status), SUCCESS);
	else if (!ft_strncmp("exit", arg[0], ft_strlen(arg[0])) && \
		ft_strlen(arg[0]) == ft_strlen("exit"))
		return (builtin_exit(arg, exit_status, env), SUCCESS);
	return (FAILED);
}

int	ft_execute_builtins(char **arg, t_env **env, int *exit_status, \
	t_pipex_data *data)
{
	int	stdout_backup;
	int	stdin_backup;
	int	result;
	int	k;

	stdout_backup = -1;
	stdin_backup = -1;
	result = FAILED;
	if (!arg || !env || !exit_status || !data || !arg[0])
		return (FAILED);
	k = setup_output_input_redirection(data->f_fd, data, &stdout_backup, \
		&stdin_backup);
	result = execute_builtin_command(arg, env, exit_status);
	restore_redirections(data->f_fd, k, stdin_backup, stdout_backup);
	return (result);
}
