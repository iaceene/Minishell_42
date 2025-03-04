/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:44:24 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/04 17:50:36 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

char *expand_variable(char *input, t_env *env) {
	(void)env;
    if (input[0] == '$') {
        char *var_name = input + 1;
        char *value = getenv(var_name);
        return value ? value : ""; // Return empty string if variable is undefined
    }
    return input;
}

// Handle quotes and variable expansion
char *handle_quotes(char *input, t_env *env) {
	ParserState state = STATE_NORMAL;
	char *result = malloc(strlen(input) + 1);
	int j = 0;

	for (int i = 0; input[i]; i++) {
		if (input[i] == '\'' && state != STATE_IN_DOUBLE_QUOTE) {
			state = (state == STATE_IN_SINGLE_QUOTE) ? STATE_NORMAL : STATE_IN_SINGLE_QUOTE;
		} else if (input[i] == '"' && state != STATE_IN_SINGLE_QUOTE) {
			state = (state == STATE_IN_DOUBLE_QUOTE) ? STATE_NORMAL : STATE_IN_DOUBLE_QUOTE;
		} else if (input[i] == '$' && state != STATE_IN_SINGLE_QUOTE) {
			char *expanded = expand_variable(input + i, env);
			strcpy(result + j, expanded);
			j += strlen(expanded);
			i += strlen(input + i) - 1; // Skip the variable name
		} else {
			result[j++] = input[i];
		}
	}
	result[j] = '\0';
	return result;
}

// Handle nested quotes (optional, for demonstration)
char *handle_nested_quotes(char *input)
{
	int single_quote_depth = 0;
	int double_quote_depth = 0;
	char *result = malloc(strlen(input) + 1);
	int j = 0;

	for (int i = 0; input[i]; i++) {
		if (input[i] == '\'' && double_quote_depth == 0) {
			single_quote_depth++;
		} else if (input[i] == '"' && single_quote_depth == 0) {
			double_quote_depth++;
		} else {
			result[j++] = input[i];
		}
	}
	result[j] = '\0';
	return result;
}

char *expander(t_node *node, t_env *env) {
	char	*expanded;

	if	(!find_it(node->value, '$')
		&& !find_it(node->value, '\'')
		&& !find_it(node->value, '"'))
		return node->value;
	expanded = handle_quotes(node->value, env);
	return expanded;
}
