/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_help2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:19:27 by iezzam            #+#    #+#             */
/*   Updated: 2025/04/09 13:03:42 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	print_export_error(char *part1, char *part2,
						int has_equal, int has_append)
{
	ft_print_err("export error: `");
	ft_print_err(part1);
	if (has_equal)
		ft_print_err("=");
	else if (has_append == 1)
		ft_print_err("+");
	ft_print_err(part2);
	ft_print_err("': invalid identifier\n");
}

int	use_equal(char **cmd)
{
	int	i;
	int	j;
	int	f;

	i = 0;
	j = 0;
	f = 0;
	while (cmd[i])
	{
		j = i;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '=')
				f++;
			j++;
		}
		i++;
	}
	if (f <= 0)
		return (-1);
	return (0);
}
