/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 02:25:14 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/03 05:32:34 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parser.h"

int starts_with(const char *str, const char *prefix)
{
    return (ft_strncmp(str, prefix, strlen(prefix)) == 0);
}

int lexer_init(const char *str)
{
    t_node *head = NULL;
    const char *current = str;

    while (*current) {
        if (ft_isspace(*current))
		{
            current++;
            continue;
        }
        // Handle multi-character operators first (&&, ||, >>, <<)
        if (starts_with(current, "&&"))
		{
            add_to_list(&head, add_new_node(AND, "&&"));
            current += 2;
            continue;
        }
		else if (starts_with(current, "||"))
		{
            add_to_list(&head, add_new_node(OR, "||"));
            current += 2;
            continue;
        }
		else if (starts_with(current, ">>"))
		{
            add_to_list(&head, add_new_node(RIGHT_APP, ">>"));
            current += 2;
            continue;
        }
		else if (starts_with(current, "<<"))
		{
            add_to_list(&head, add_new_node(LEFT_APP, "<<"));
            current += 2;
            continue;
        }
        // Handle single-character operators (|, >, <)
        if (*current == '|')
		{
            add_to_list(&head, add_new_node(PIPE, "|"));
            current++;
            continue;
        }
		else if (*current == '>')
		{
            add_to_list(&head, add_new_node(RIGHT_RED, ">"));
            current++;
            continue;
        }
		else if (*current == '<')
		{
            add_to_list(&head, add_new_node(LEFT_RED, "<"));
            current++;
            continue;
        }
        // Handle dollar sign ($)
        if (*current == '$')
		{
            add_to_list(&head, add_new_node(DOLLAR, "$"));
            current++;
            continue;
        }
		// single q
        if (*current == '\'')
		{
            add_to_list(&head, add_new_node(SIN_QUOTE, "\'"));
            current++;
            continue;
        }
		// double q
        if (*current == '"')
		{
            add_to_list(&head, add_new_node(DOB_QUOTE, "\""));
            current++;
            continue;
        }
		// handel words
		if (ft_isalnum(*current))
		{
			add_to_list(&head, add_new_node(WORD, extract_word((char *)current)));
			while (*current && (ft_isalnum(*current) || ft_isspace(*current) || *current == '-'))
				current++;
			continue;
		}
        current++;
    }

    t_node *temp = head;
    while (temp)
	{
        printf("Token: %s, Type: %d\n", temp->value, temp->type);
        temp = temp->next;
    }
    return 0;
}
