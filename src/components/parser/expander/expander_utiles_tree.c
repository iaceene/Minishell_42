/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utiles_tree.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:19:22 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/22 19:57:43 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

void	set_space_excep(char *tmp)
{
	int	i;

	i = 0;
	if (!tmp)
		return ;
	while (tmp[i])
	{
		if (ft_isspace(tmp[i]))
			tmp[i] = -13;
		i++;
	}
}

void	replace_character(char *s, int re)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != re)
			s[j++] = s[i];
		i++;
	}
	s[j] = '\0';
}

void	set_zero_space(char **s)
{
	int	i;
	int	j;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] == -1)
				s[i][j] = ' ';
			j++;
		}
		i++;
	}
}

void	set_space_zero_qoats(char *tmp)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	if (!tmp)
		return ;
	while (tmp[i])
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
			in_quotes = !in_quotes;
		if (ft_isspace(tmp[i]) && in_quotes)
			tmp[i] = -1;
		i++;
	}
}

void	set_space_zero(char *tmp)
{
	int	i;

	i = 0;
	if (!tmp)
		return ;
	while (tmp[i])
	{
		if (ft_isspace(tmp[i]))
			tmp[i] = -1;
		i++;
	}
}
