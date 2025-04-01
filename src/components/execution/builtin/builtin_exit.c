/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneki <kaneki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 01:52:48 by iezzam            #+#    #+#             */
/*   Updated: 2025/04/01 15:40:08 by kaneki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

static void	ft_print_error(char *src, int exit_code)
{
	if (!src)
		return ;
	write(2, src, ft_strlen(src));
	write(2, "\n", 1);
	if (exit_code >= 0)
		exit(exit_code);
}

static int	ft_is_numeric(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_atoll_exit(char *str)
{
	long long	num;
	int			sign;
	int			i;

	num = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	else
		sign = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		if (num > LLONG_MAX / 10 || \
			(num == LLONG_MAX / 10 && (str[i] - '0' > 7)))
			ft_print_error("exit: numeric argument required", 2);
		num = num * 10 + (str[i++] - '0');
	}
	if (str[i])
		ft_print_error("exit: numeric argument required", 2);
	return ((num * sign) % 256);
}

void	builtin_exit(char **arg, int *exit_status, t_env **env)
{
	int	exit_code;

	if (!arg[1])
	{
		ft_print_error("exit", -1);
		exit(0);
	}
	if (!ft_is_numeric(arg[1]))
		ft_print_error("exit: numeric argument required", 2);
	if (arg[2])
	{
		ft_print_error("exit: too many arguments", 1);
		*exit_status = 1;
		return ;
	}
	exit_code = ft_atoll_exit(arg[1]);
	ft_env_clear(env);
	exit(exit_code);
}
