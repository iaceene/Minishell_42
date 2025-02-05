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

int	ft_execute_builtins(char **arg, t_env **env, int *exit_status)
{
	if (!arg || !(*arg))
		return (*exit_status = 0, SUCCESS);
	else if (!ft_strncmp("env", arg[0], ft_strlen(arg[0])))
		return (builtin_env(*env, arg, exit_status), SUCCESS);
	else if (!ft_strncmp("exit", arg[0], ft_strlen(arg[0])))
		return (builtin_exit(arg, exit_status, env), SUCCESS);
	else if (!ft_strncmp("echo", arg[0], ft_strlen(arg[0])))
		return (builtin_echo(arg), *exit_status = 0, SUCCESS);
	else if (!ft_strncmp("cd", arg[0], ft_strlen(arg[0])))
		return (builtin_cd(arg, env, exit_status), SUCCESS);
	else if (!ft_strncmp("export", arg[0], ft_strlen(arg[0])))
		return (builtin_export(env, arg, exit_status), SUCCESS);
	else if (!ft_strncmp("pwd", arg[0], ft_strlen(arg[0])))
		return (builtin_pwd(), *exit_status = 0, SUCCESS);
	else if (!ft_strncmp("unset", arg[0], ft_strlen(arg[0])))
		return (builtin_unset(env, arg, exit_status), SUCCESS);
	else
		return (FAILED);
}