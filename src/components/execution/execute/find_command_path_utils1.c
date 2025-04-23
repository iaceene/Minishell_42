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

static int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

char	*find_command_path(char *cmd, char **env)
{
	char	*path;
	char	*result;

	if (!cmd)
		return (NULL);
	if (ft_strcmp(cmd, "./") == 0 || cmd[0] == '/' || ft_strchr(cmd, '/'))
	{
		if (is_directory(cmd))
			(ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmd, 2), \
			ft_putstr_fd(": Is a directory\n", 2), exit (126));
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else if (access(cmd, F_OK) == 0)
		{
			(ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmd, 2), \
			ft_putstr_fd(": Permission denied\n", 2), exit(1));
		}
		else
			(ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmd, 2), \
			ft_putstr_fd(": No such file or directory\n", 2), exit(127));
	}
	path = get_path_variable(env);
	if (!path)
		return (NULL);
	return (result = find_executable_in_path(path, cmd));
}
