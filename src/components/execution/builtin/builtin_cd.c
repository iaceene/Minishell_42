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

#include "../../../../include/execution.h"

static int	update_env_paths(t_env **env, char *prev_wd, char *new_path)
{
	char	cwd[MAXPATHLEN];
	char	*cwd_value;
	int		ex_status;

	ex_status = 0;
	if (prev_wd)
	{
		ft_env_delete(env, "OLDPWD");
		ft_env_add(env, ft_strdup("OLDPWD"), ft_strdup(prev_wd), 1);
	}
	if (getcwd(cwd, MAXPATHLEN) == NULL)
	{
		perror("cd: error retrieving current directory: getcwd failed");
		ex_status = 1;
	}
	cwd_value = ft_get_cwd(new_path, 1);
	if (cwd_value)
		ft_env_update(env, ft_strdup("PWD"), cwd_value, 0);
	return (ex_status);
}

static int	change_to_path(t_env **env, char *target_path, int print_path)
{
	char	*prev_wd;
	int		exit_status;
	char	*error_msg;

	prev_wd = ft_get_cwd(NULL, 0);
	if (chdir(target_path) == SUCCESS)
	{
		exit_status = update_env_paths(env, prev_wd, target_path);
		if (print_path)
			printf("%s\n", target_path);
	}
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
	int		print_path;

	print_path = 0;
	if (!ft_env_search(*env, "PWD") && getcwd(cwd, MAXPATHLEN))
		ft_env_add(env, ft_strdup("PWD"), ft_strdup(cwd), 1);
	if (!arg[1] || !ft_strcmp("~", arg[1]))
		target_path = ft_env_search(*env, "HOME");
	else if (!ft_strcmp("-", arg[1]))
		(1) && (print_path = 1, target_path = ft_env_search(*env, "OLDPWD"));
	else
		target_path = arg[1];
	if (!target_path)
	{
		if (!arg[1] || !ft_strcmp("~", arg[1]))
			ft_print_err("cd: HOME not set\n");
		else
			ft_print_err("cd: OLDPWD not set\n");
		return (*exit_status = 1);
	}
	if (!*target_path)
		return (*exit_status = 0);
	return (*exit_status = change_to_path(env, target_path, print_path));
}
