/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:30:27 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/28 09:34:35 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static char	*get_path_variable(char **env)
{
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	return (ft_strdup(env[i] + 5));
}

static char	*check_command_in_dir(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	return (NULL);
}

static char	*find_executable_in_path(char *path, char *cmd)
{
	char	*dir;
	char	*full_path;

	dir = ft_strtok(path, ":");
	while (dir)
	{
		full_path = check_command_in_dir(dir, cmd);
		if (full_path)
			return (full_path);
		dir = ft_strtok(NULL, ":");
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **env)
{
	char	*path;
	char	*result;

	if (!cmd)
		return (NULL);
	if (ft_strncmp(cmd, "./", 2) == 0 || cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	path = get_path_variable(env);
	if (!path)
		return (NULL);
	result = find_executable_in_path(path, cmd);
	return (result);
}

void	execute_cmd(char **cmd, char **env, int *exit_status)
{
	char	**args;
	char	*full_path;

	args = cmd;
	if (!env)
	{
		write(2, "shell: env is NULL\n", 19);
		*exit_status = 127;
	}
	full_path = find_command_path(args[0], env);
	if (!full_path)
	{
		write(2, "command not found: ", 19);
		write(2, args[0], ft_strlen(args[0]));
		write(2, "\n", 1);
		*exit_status = 127;
		exit(127);
	}
	args[0] = full_path;
	if (execve(full_path, args, env) == -1)
	{
		*exit_status = 126;
		perror("exec failed\n");
		exit(126);
	}
}
