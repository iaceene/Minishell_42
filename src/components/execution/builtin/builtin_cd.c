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

static int	update_pwd(t_env **env, char *new_path)
{
	char	*cwd;
	char	*cwd_value;
	t_env	*pwd;
	int		ex_status;

	ex_status = 0;
	if (!new_path)
		return (1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd: error retrieving current directory: getcwd failed");
		ex_status = 1;
	}
	cwd_value = ft_get_cwd(new_path, 1);
	if (!cwd_value)
		return (free(cwd), ex_status);
	pwd = *env;
	while (pwd && ft_strcmp(pwd->key, "PWD") != 0)
		pwd = pwd->next;
	if (pwd)
		pwd->value = cwd_value;
	else
		ft_env_add(env, ft_strdup("PWD"), cwd_value, 1);
	return (free(cwd), ex_status);
}

static int	update_env_paths(t_env **env, char *prev_wd, char *new_path)
{
	int	oldpwd_status;
	int	pwd_status;

	oldpwd_status = update_oldpwd(env, prev_wd);
	pwd_status = update_pwd(env, new_path);
	if (pwd_status != 0)
		return (pwd_status);
	return (oldpwd_status);
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

int	builtin_cd_help(char *target_path, char **arg)
{
	if (!target_path)
	{
		if (!arg[1] || !ft_strcmp("~", arg[1]))
			ft_print_err("cd: HOME not set\n");
		else
			ft_print_err("cd: OLDPWD not set\n");
		return (1);
	}
	return (0);
}

int	builtin_cd(char **arg, t_env **env, int *exit_status)
{
	char	*target_path;
	char	*cwd;
	int		print_path;

	cwd = NULL;
	print_path = 0;
	cwd = getcwd(NULL, 0);
	if (!ft_env_search(*env, "PWD") && cwd)
		(ft_env_add(env, ft_strdup("PWD"), ft_strdup(cwd), 1), free(cwd));
	else if (cwd)
		free(cwd);
	target_path = get_target_path(arg, env, &print_path);
	if (builtin_cd_help(target_path, arg))
		return (*exit_status = 1);
	if (!*target_path)
		return (*exit_status = 0);
	return (*exit_status = change_to_path(env, target_path, print_path));
}
