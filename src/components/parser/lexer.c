/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 02:25:14 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/03 03:03:08 by yaajagro         ###   ########.fr       */
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
    char *token = NULL;
    size_t token_len = 0;

    while (*current) {
        // Skip whitespace
        if (ft_isspace(*current))
		{
            current++;
            continue;
        }
        // Handle multi-character operators first (&&, ||, >>, <<)
        if (starts_with(current, "&&"))
		{
            add_to_list(&head, add_new_node(TOKEN_AND, "&&"));
            current += 2;
            continue;
        }
		else if (starts_with(current, "||"))
		{
            add_to_list(&head, add_new_node(TOKEN_OR, "||"));
            current += 2;
            continue;
        }
		else if (starts_with(current, ">>"))
		{
            add_to_list(&head, add_new_node(TOKEN_REDIRECT, ">>"));
            current += 2;
            continue;
        }
		else if (starts_with(current, "<<"))
		{
            add_to_list(&head, add_new_node(TOKEN_REDIRECT, "<<"));
            current += 2;
            continue;
        }
        // Handle single-character operators (|, >, <)
        if (*current == '|')
		{
            add_to_list(&head, add_new_node(TOKEN_PIPE, "|"));
            current++;
            continue;
        }
		else if (*current == '>')
		{
            add_to_list(&head, add_new_node(TOKEN_REDIRECT, ">"));
            current++;
            continue;
        }
		else if (*current == '<')
		{
            add_to_list(&head, add_new_node(TOKEN_REDIRECT, "<"));
            current++;
            continue;
        }
        // Handle dollar sign ($)
        if (*current == '$')
		{
            add_to_list(&head, add_new_node(TOKEN_DOLLAR, "$"));
            current++;
            continue;
        }

        // Handle quotes (both single and double)
        if (*current == '"' || *current == '\'')
		{
            char quote_char = *current;
            current++;  // Skip the opening quote
            // Collect the word inside the quotes
            token_len = 0;
            token = malloc(sizeof(char));  // Start with a small allocation
            if (!token)
				return -1; // Check malloc failure
            while (*current && *current != quote_char)
			{
                token[token_len++] = *current++;
                token = realloc(token, token_len + 1);  // Reallocate space for the next character
                if (!token)
					return -1;  // Check realloc failure
            }
            token[token_len] = '\0';  // Null terminate the token
            if (*current == quote_char)
                current++;  // Skip the closing quote
				
            add_to_list(&head, add_new_node(TOKEN_QUOTE, token));
            free(token);  // Free the dynamically allocated token memory
            continue;
        }
        // Handle words (commands/arguments)
        if (ft_isalnum(*current) || *current == '-')
		{
            token_len = 0;
            token = malloc(sizeof(char));  // Start with a small allocation
            if (!token)
				return -1;  // Check malloc failure
            // Collect the word
            while (*current && (ft_isalnum(*current) || *current == '-'))
			{
                token[token_len++] = *current++;
                token = realloc(token, token_len + 1);  // Reallocate space for the next character
                if (!token) return -1;  // Check realloc failure
            }
            token[token_len] = '\0';  // Null terminate the token
            add_to_list(&head, add_new_node(TOKEN_WORD, token));
            free(token);  // Free the dynamically allocated token memory
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
