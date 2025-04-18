/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:35:51 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/26 19:54:22 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

t_node	*add_new_node(t_TokenType type, char *val)
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

int	is_inside_quotes(char *str, char *cur)
{
	int	single_quotes;
	int	double_quotes;

	single_quotes = 0;
	double_quotes = 0;
	while (str < cur)
	{
		if (*str == '\'' && !double_quotes)
			single_quotes = !single_quotes;
		else if (*str == '"' && !single_quotes)
			double_quotes = !double_quotes;
		str++;
	}
	return (single_quotes || double_quotes);
}

int	operator(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '(' || c == ')');
}

char	*extract_word(char *s)
{
	char	*tmp;
	int		len;
	char	*start;
	int		in_quotes;
	char	quote_char;

	in_quotes = 0;
	quote_char = 0;
	s = skip_spaces(s);
	start = s;
	len = calculate_word_length(s, &in_quotes, &quote_char);
	tmp = ft_malloc(len + 1);
	copy_word(tmp, start, len);
	while (len > 0 && tmp[len - 1] == ' ')
		tmp[--len] = '\0';
	return (tmp);
}
