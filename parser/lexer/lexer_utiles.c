/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:35:51 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/11 23:15:29 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

t_node	*add_new_node(TokenType type, char *val)
{
	t_node	*ret;

	ret = ft_malloc(sizeof(t_node));
	ret->visit = false;
	ret->type = type;
	ret->value = ft_strdup(val);
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

int	ft_isalnum(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

int	operator(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '(' || c == ')');
}

char	*extract_word(char *s)
{
	char	*tmp;
	int		i;
	int		len;
	char	*start;

	while (*s == ' ')
		s++;
	start = s;
	len = 0;
	while (*s && !operator(*s))
	{
		s++;
		len++;
	}
	tmp = ft_malloc(len + 1);
	i = 0;
	while (i < len)
	{
		tmp[i] = start[i];
		i++;
	}
	tmp[len] = '\0';
	while (len > 0 && tmp[len - 1] == ' ')
		tmp[--len] = '\0';
	return (tmp);
}
