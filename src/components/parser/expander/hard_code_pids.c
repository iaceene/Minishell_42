/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_code_pids.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:17:22 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/11 20:35:29 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

char	*set_dollars(char *exp)
{
	int	i;

	i = 0;
	while (exp[i])
	{
		if (exp[i] == -12)
			exp[i] = '$';
		i++;
	}
	return (exp);
}

void	hard_code_pid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1] && str[i] == '$' && str[i + 1] == '$')
		{
			str[i] = '1';
			str[i + 1] = '3';
		}
		if (str[i] == '$' && is_sperator(str[i + 1]))
			str[i] = -12;
		i++;
	}
	if (str[i - 1] == '$')
		str[i - 1] = -12;
}
