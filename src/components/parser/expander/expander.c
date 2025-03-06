/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:44:24 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/06 00:30:32 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

typedef struct s_expand
{
	State			state;
	char			*val;
	struct s_expand	*next;
}	t_expand;


t_expand	*new_expand(State state, char *val);
void		add_expand(t_expand **head, t_expand *new);
char		*expand_and_join(t_expand *head);

char *handle_quotes(char *input)
{
	t_expand	*head;
	t_expand	*node;
	State		state;
	char		*start;

	head = NULL;
	state = NORMAL;
	while (*input)
	{
		if (*input == '\'' && state == NORMAL) // Enter single-quoted mode
		{
			state = IN_SQUOTE;
			input++;
			start = input;
			while (*input && *input != '\'') // Collect inside single quotes
				input++;
			node = new_expand(state, ft_substr(start, 0, input - start));
			add_expand(&head, node);
			if (*input) // Skip closing quote
				input++;
			state = NORMAL;
		}
		else if (*input == '"' && state == NORMAL) // Enter double-quoted mode
		{
			state = IN_DQUOTE;
			input++;
			start = input;
			while (*input && *input != '"') // Collect inside double quotes
				input++;
			node = new_expand(state, ft_substr(start, 0, input - start));
			add_expand(&head, node);
			if (*input) // Skip closing quote
				input++;
			state = NORMAL;
		}
		else // Normal text (outside quotes)
		{
			start = input;
			while (*input && *input != '\'' && *input != '"')
				input++;
			node = new_expand(state, ft_substr(start, 0, input - start));
			add_expand(&head, node);
		}
	}
	t_expand *tmp = head;
	while (tmp)
	{
		printf("val: %s, state: %d\n", tmp->val, tmp->state);
		tmp = tmp->next;
	}
	return (expand_and_join(head));
}

char	*expand_this(char *str)
{
	char	*env_name;
	char	*env_value;

	if (!str || str[0] != '$')
		return (ft_strdup(str));

	env_name = str + 1; 
	env_value = getenv(env_name); // Get environment variable value

	if (!env_value) // If variable doesn't exist, return empty string
		return (ft_strdup(""));

	return (ft_strdup(env_value)); // Return the expanded value
}

char	*expand_and_join(t_expand *head)
{
	char	*buffer;
	char	*tmp;

	buffer = NULL;
	while (head)
	{
		if (head->state != IN_SQUOTE && find_it(head->val, '$'))
			tmp = expand_this(head->val);
		else
			tmp = ft_strdup(head->val);
		buffer = ft_strjoin(buffer, tmp);
		head = head->next;
	}
	return (buffer);
}

char *expander(t_node *node, t_env *env)
{
	(void)env;
	char	*expanded;

	if	(!find_it(node->value, '$')
		&& !find_it(node->value, '\'')
		&& !find_it(node->value, '"'))
		return node->value;
	expanded = handle_quotes(node->value);
	printf("%s\n", expanded);
	return expanded;
}

void	add_expand(t_expand **head, t_expand *new)
{
	t_expand	*tmp;

	tmp = *head;
	if (!*head)
	{
		*head = new;
		return ;
	}
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_expand	*new_expand(State state, char *val)
{
	t_expand	*ret;

	ret = ft_malloc(sizeof(t_expand));
	ret->next = NULL;
	ret->state = state;
	ret->val = val;
	return (ret);
}
