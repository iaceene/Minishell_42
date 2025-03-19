/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:04:09 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/27 13:07:01 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static int	update_env_paths(t_env **env, char *prev_wd, char *new_path)
{
	char	cwd[MAXPATHLEN];
	char	*cwd_value;
	int		ex_status;

	ex_status = 0;
	ft_env_delete(env, "OLDPWD");
	ft_env_add(env, ft_strdup("OLDPWD"), prev_wd, 1);
	if (getcwd(cwd, MAXPATHLEN) == NULL)
	{
		perror("cd: error retrieving current directory: getcwd failed");
		ex_status = 1;
	}
	cwd_value = ft_get_cwd(new_path, 1);
	if (cwd_value)
	{
		ft_env_update(env, ft_strdup("PWD"), cwd_value, 0);
	}
	return (ex_status);
}

static int	change_to_path(t_env **env, char *target_path)
{
	char	*prev_wd;
	int		exit_status;
	char	*error_msg;

	prev_wd = ft_get_cwd(NULL, 0);
	if (chdir(target_path) == SUCCESS)
		exit_status = update_env_paths(env, prev_wd, target_path);
	else
	{
		error_msg = ft_strjoin("cd: ", target_path);
		perror(error_msg);
		exit_status = 1;
	}
	return (exit_status);
}

int	builtin_cd(char **arg, t_env **env, int *exit_status)
{
	char	*target_path;
	char	cwd[MAXPATHLEN];

	if (!ft_env_search(*env, "PWD"))
	{
		if (getcwd(cwd, MAXPATHLEN))
			ft_env_add(env, ft_strdup("PWD"), ft_strdup(cwd), 1);
		else
			(perror("cd: error setting initial PWD"), *exit_status = 1);
	}
	if (!ft_env_search(*env, "OLDPWD"))
		ft_env_add(env, ft_strdup("OLDPWD"), ft_strdup(""), 1);
	if (!arg[1] || !ft_strncmp("~", arg[1], 1))
		target_path = ft_env_search(*env, "HOME");
	else if (!ft_strncmp("-", arg[1], 1))
		target_path = ft_env_search(*env, "OLDPWD");
	else
		target_path = arg[1];
	if (!target_path || !*target_path)
	{
		(ft_print_err("cd: HOME or OLDPWD not set\n"), *exit_status = 1);
		return (1);
	}
	*exit_status = change_to_path(env, target_path);
	return (0);
}
