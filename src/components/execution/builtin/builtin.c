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

#include "../../../../include/minishell.h"

int setup_output_input_redirection(int f_fd, t_pipex_data *data, int *stdout_backup, int *stdin_backup)
{
	int rest;

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

int restore_redirections(int f_fd, int k, int stdin_backup, int stdout_backup)
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
	return 0;
}

int ft_execute_builtins(char **arg, t_env **env, int *exit_status, t_pipex_data *data, int f_fd)
{
	int	stdout_backup;
	int	stdin_backup;
	int	result;
	int	k;

	if (!arg || !env || !exit_status || !data || !arg[0])
		return FAILED;
	result = FAILED;
	stdout_backup = -1;
	stdin_backup = -1;
	k = setup_output_input_redirection(f_fd, data, &stdout_backup, &stdin_backup);
	if (arg[0] && !ft_strncmp("env", arg[0], ft_strlen(arg[0])) && ft_strlen(arg[0]) == ft_strlen("env"))
		(builtin_env(*env, arg, exit_status), result = SUCCESS);
	else if (!ft_strncmp("echo", arg[0], ft_strlen(arg[0])) &&  ft_strlen(arg[0]) == ft_strlen("echo"))
		(builtin_echo(arg), *exit_status = 0, result = SUCCESS);
	else if (!ft_strncmp("cd", arg[0], ft_strlen(arg[0])) &&  ft_strlen(arg[0]) == ft_strlen("cd"))
		(builtin_cd(arg, env, exit_status), result = SUCCESS);
	else if (!ft_strncmp("export", arg[0], ft_strlen(arg[0])) &&  ft_strlen(arg[0]) == ft_strlen("export"))
		(builtin_export(env, arg, exit_status), result = SUCCESS);
	else if (!ft_strncmp("pwd", arg[0], ft_strlen(arg[0])) && ft_strlen(arg[0]) == ft_strlen("pwd"))
		(builtin_pwd(), *exit_status = 0, result = SUCCESS);
	else if (!ft_strncmp("unset", arg[0], ft_strlen(arg[0])) && ft_strlen(arg[0]) == ft_strlen("unset"))
		(builtin_unset(env, arg, exit_status), result = SUCCESS);
	restore_redirections(f_fd, k, stdin_backup, stdout_backup);
	return (result);
}
