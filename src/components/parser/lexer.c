/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 02:25:14 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/08 09:26:10 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../include/parser.h"

int operator(char c)
{
    return (c == '<' || c == '>' || c == '|' || c == '(' || c == ')' || c == '"'
        || c == '\'');
}

int starts_with(const char *str, const char *prefix)
{
    return (ft_strncmp(str, prefix, strlen(prefix)) == 0);
}

void	other_oper(t_node **head, char *s)
{
	if (starts_with(s, "'"))
		add_to_list(head, add_new_node(SIN_QUOTE, "'"));
	else if (starts_with(s, "\""))
		add_to_list(head, add_new_node(DOB_QUOTE, "\""));
	else if (starts_with(s, "("))
		add_to_list(head, add_new_node(OPEN_PAR, "("));
	else if (starts_with(s, ")"))
		add_to_list(head, add_new_node(CLOSE_PAR, ")"));
	else if (starts_with(s, "$"))
		add_to_list(head, add_new_node(DOLLAR, "$"));
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

	while (*s && ft_isspace(*s))
		s++;
	if (!*s)
		return (NULL);
	command = extract_word(s);
	add_to_list(head, add_new_node(COMMAND, command));
	while (*s && !operator(*s))
		s++;
	return (s);
}

t_node	*lexer_init(const char *str)
{
	t_node	*head;
	char	*cur;

	head = NULL;
	cur = (char *)str;
	while (*cur)
	{
		while (ft_isspace(*cur))
			cur++;
		if (operator(*cur))
			cur = oper_tock(&head, cur);
		else if (!operator(*cur))
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
