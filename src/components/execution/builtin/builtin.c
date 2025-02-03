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

int	ft_execute_builtins(char **cmd_2d, t_env **env, int *exit_status)
{
	if (!cmd_2d || !(*cmd_2d))
		return (*exit_status = 0, SUCCESS);
	else if (!ft_strncmp("env", cmd_2d[0], ft_strlen(cmd_2d[0])))
		return (builtin_env(*env, cmd_2d, exit_status), SUCCESS);
	else if (!ft_strncmp("exit", cmd_2d[0], ft_strlen(cmd_2d[0])))
		return (builtin_exit(cmd_2d, exit_status, env), SUCCESS);
	else if (!ft_strncmp("echo", cmd_2d[0], ft_strlen(cmd_2d[0])))
		return (builtin_echo(cmd_2d), *exit_status = 0, SUCCESS);
	else if (!ft_strncmp("cd", cmd_2d[0], ft_strlen(cmd_2d[0])))
		return (builtin_cd(cmd_2d, env, exit_status), SUCCESS);
	else if (!ft_strncmp("export", cmd_2d[0], ft_strlen(cmd_2d[0])))
		return (builtin_export(env, cmd_2d, exit_status), SUCCESS);
	else if (!ft_strncmp("pwd", cmd_2d[0], ft_strlen(cmd_2d[0])))
		return (builtin_pwd(), *exit_status = 0, SUCCESS);
	else if (!ft_strncmp("unset", cmd_2d[0], ft_strlen(cmd_2d[0])))
		return (builtin_unset(env, cmd_2d, exit_status), SUCCESS);
	else
		return (FAILED);
}