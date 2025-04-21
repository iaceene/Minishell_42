/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_code_pids.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:17:22 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/21 19:09:48 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

char	*set_dollars(char *exp)
{
	int	i;

	i = 0;
	if (!exp)
		return (NULL);
	while (exp[i])
	{
		if (exp[i] == -12)
			exp[i] = '$';
		i++;
	}
	return (exp);
}

int	to_skipp(int c)
{
	return (c == '.' || c == ',' || c == ';');
}

void	hard_code_pid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1] && str[i] == '$' && str[i + 1] == '$')
		{
			str[i] = '$';
			str[i + 1] = '$';
		}
		if (str[i] == '$' && is_sperator(str[i + 1]))
			str[i] = -12;
		if (str[i + 1] && str[i] == '$' && to_skipp(str[i + 1]))
			str[i] = -12;
		i++;
	}
	if (str[i - 1] == '$')
		str[i - 1] = -12;
}
