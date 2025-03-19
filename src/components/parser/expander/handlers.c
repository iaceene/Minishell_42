/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:29:48 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/18 21:40:41 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

void	handle_single_quote(char **input, t_expand **head, t_state *state)
{
	char		*start;
	char		*tmp;
	t_expand	*node;

	*state = IN_SQUOTE;
	(*input)++;
	start = *input;
	while (**input && **input != '\'')
		(*input)++;
	tmp = ft_substr(start, 0, *input - start);
	set_space_zero(tmp);
	node = new_expand(*state, tmp);
	add_expand(head, node);
	if (**input)
		(*input)++;
	*state = NORMAL;
}

void	handle_double_quote(char **input, t_expand **head, t_state *state)
{
	char		*start;
	char		*tmp;
	t_expand	*node;

	*state = IN_DQUOTE;
	(*input)++;
	start = *input;
	while (**input && **input != '"')
		(*input)++;
	tmp = ft_substr(start, 0, *input - start);
	set_space_zero(tmp);
	node = new_expand(*state, tmp);
	add_expand(head, node);
	if (**input)
		(*input)++;
	*state = NORMAL;
}

void	handle_normal_text(char **input, t_expand **head, t_state state)
{
	char		*start;
	t_expand	*node;

	start = *input;
	while (**input && **input != '\'' && **input != '"')
		(*input)++;
	node = new_expand(state, ft_substr(start, 0, *input - start));
	add_expand(head, node);
}

void	set_space_zero(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == ' ')
			tmp[i] = -1;
		i++;
	}
}

void	set_space_zero_qoats(char *tmp)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
			in_quotes = !in_quotes;
		if (tmp[i] == ' ' && in_quotes)
			tmp[i] = -1;
		i++;
	}
}

void	set_zero_space(char **s)
{
	int i;
	int	j;

	i = 0;
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
