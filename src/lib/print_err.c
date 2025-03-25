/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 22:16:01 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/31 17:27:24 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_err(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
}

void	ft_puterr(int state)
{
	if (state == 1)
		ft_print_err("Invalid env!\n");
	if (state == 3)
		ft_print_err("ambiguous redirect\n");
	if (state == 14)
		ft_print_err("\033[31mError\033[0m : Invalid syntax\n");
	if (state == 17)
		ft_print_err("Command '' not found\n");
}
