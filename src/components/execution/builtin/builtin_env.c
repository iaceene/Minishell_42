/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:11:50 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/27 10:34:44 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

void	builtin_env(t_env *env, char **arg, int *exit_status)
{
	if (arg[1])
	{
		ft_print_err("env: invalid argument\n");
		*exit_status = 127;
		return ;
	}
	ft_print_env(env);
	*exit_status = 0;
}
