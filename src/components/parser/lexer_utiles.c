/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:35:51 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/03 02:24:01 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parser.h"

t_node	*add_new_node(TokenType type, char *val)
{
	t_node *ret;

	ret = ft_malloc(sizeof(t_node));
	ret->type = type;
	ret->value = val;
	ret->next = NULL;
	return (ret);
}

void	add_to_list(t_node **head, t_node *new)
{
	t_node	*last;
	
	if (!head)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	else
	{
		last = *head;
		while (last && last->next)
			last = last->next;
		last->next = new;
	}
}
