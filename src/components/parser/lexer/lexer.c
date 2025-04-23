/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 02:25:14 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/23 15:26:13 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

int	starts_with(const char *str, const char *prefix)
{
	return (ft_strncmp(str, prefix, ft_strlen(prefix)) == 0);
}

void	other_oper(t_node **head, char *s)
{
	if (starts_with(s, "("))
		add_to_list(head, add_new_node(OPEN_PAR, "("));
	else if (starts_with(s, ")"))
		add_to_list(head, add_new_node(CLOSE_PAR, ")"));
}

char	*oper_tock(t_node **head, char *s)
{
	int	len;

	len = 1;
	if (starts_with(s, "<<"))
	{
		add_to_list(head, add_new_node(HERDOC, "<<"));
		len = 2;
	}
	else if (starts_with(s, ">>"))
	{
		add_to_list(head, add_new_node(APPEND, ">>"));
		len = 2;
	}
	else if (starts_with(s, "<"))
		add_to_list(head, add_new_node(LEFT_RED, "<"));
	else if (starts_with(s, ">"))
		add_to_list(head, add_new_node(RIGHT_RED, ">"));
	else if (starts_with(s, "|"))
		add_to_list(head, add_new_node(PIPE, "|"));
	else
		other_oper(head, s);
	return (s + len);
}

char	*add_command(t_node **head, char *s)
{
	char	*command;
	int		in_quotes;
	char	quote_char;

	if (!s)
		return (NULL);
	in_quotes = 0;
	quote_char = 0;
	s = skip_spaces(s);
	if (!*s)
		return (ft_strdup(""));
	command = extract_word(s);
	if (!command)
		return (ft_strdup(""));
	add_to_list(head, add_new_node(COMMAND, command));
	s = handle_qoa_cmd(s, &in_quotes, &quote_char);
	return (s);
}

t_node	*lexer_init(const char *str)
{
	t_node	*head;
	char	*cur;

	head = NULL;
	if (!str)
		return (NULL);
	cur = (char *)str;
	while (*cur)
	{
		while (ft_isspace(*cur))
			cur++;
		if (operator(*cur) && !is_inside_quotes((char *)str, cur))
			cur = oper_tock(&head, cur);
		else if (!operator(*cur) || is_inside_quotes((char *)str, cur))
		{
			cur = add_command(&head, cur);
			if (!cur)
				return (head);
		}
		else
			cur++;
	}
	return (head);
}
