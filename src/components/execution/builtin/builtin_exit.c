/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:07:33 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/27 13:06:06 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

static void	ft_print_error(char *msg, int exit_code)
{
	if (!msg)
		return;
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	if (exit_code >= 0)
		exit(exit_code);
}

static int	ft_is_numeric(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = (str[0] == '-' || str[0] == '+') ? 1 : 0;
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
	sign = (str[i] == '-') ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		if (num > LLONG_MAX / 10 || (num == LLONG_MAX / 10 && (str[i] - '0' > 7)))
			ft_print_error("exit: numeric argument required", 255);
		num = num * 10 + (str[i++] - '0');
	}
	if (str[i]) // Handle invalid characters after numbers
		ft_print_error("exit: numeric argument required", 255);
	return ((num * sign) % 256);
}

void	builtin_exit(char **cmd_2d, int *exit_status, t_env **env)
{
	int	exit_code;

	printf("exit\n");
	if (!cmd_2d[1])
		exit(0);
	if (!ft_is_numeric(cmd_2d[1]))
		ft_print_error("exit: numeric argument required", 255);
	if (cmd_2d[2])
	{
		ft_print_error("exit: too many arguments", -1);
		*exit_status = 1;
		return;
	}
	exit_code = ft_atoll_exit(cmd_2d[1]);
	ft_env_clear(env);
	exit(exit_code);
}
