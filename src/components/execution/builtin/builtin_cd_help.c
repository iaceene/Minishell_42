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

int	update_oldpwd(t_env **env, char *prev_wd)
{
	t_env	*oldpwd;

	if (!prev_wd)
		return (0);
	oldpwd = *env;
	while (oldpwd && ft_strcmp(oldpwd->key, "OLDPWD") != 0)
		oldpwd = oldpwd->next;
	if (oldpwd)
		oldpwd->value = ft_strdup(prev_wd);
	else
		ft_env_add(env, ft_strdup("OLDPWD"), ft_strdup(prev_wd), 1);
	return (0);
}

char	*get_target_path(char **arg, t_env **env, int *print_path)
{
	char	**spl;
	char	*target_path;

	*print_path = 0;
	if (arg[1] && ft_strncmp("~/", arg[1], 2) == 0)
		(1) && (spl = ft_split(arg[1], '~'), \
		target_path = ft_strjoin(ft_env_search(*env, "HOME"), spl[0]));
	else if (!arg[1])
		target_path = ft_env_search(*env, "HOME");
	else if (!ft_strcmp("-", arg[1]))
		(1) && (*print_path = 1, target_path = ft_env_search(*env, "OLDPWD"));
	else
		target_path = arg[1];
	return (target_path);
}
