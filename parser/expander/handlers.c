/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:29:48 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/11 23:54:07 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

void	handle_single_quote(char **input, t_expand **head, t_state *state)
{
	char		*start;
	t_expand	*node;

	*state = IN_SQUOTE;
	(*input)++;
	start = *input;
	while (**input && **input != '\'')
		(*input)++;
	node = new_expand(*state, ft_substr(start, 0, *input - start));
	add_expand(head, node);
	if (**input)
		(*input)++;
	*state = NORMAL;
}

void	handle_double_quote(char **input, t_expand **head, t_state *state)
{
	char		*start;
	t_expand	*node;

	*state = IN_DQUOTE;
	(*input)++;
	start = *input;
	while (**input && **input != '"')
		(*input)++;
	node = new_expand(*state, ft_substr(start, 0, *input - start));
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
