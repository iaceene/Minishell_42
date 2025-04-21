/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:44:24 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/21 21:01:05 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

char	*handle_quotes(char *input, t_env *env, int exit)
{
	t_expand	*head;
	t_state		state;

	head = NULL;
	state = NORMAL;
	while (*input)
	{
		if (*input == '\'' && state == NORMAL)
			handle_single_quote(&input, &head, &state);
		else if (*input == '"' && state == NORMAL)
			handle_double_quote(&input, &head, &state);
		else
			handle_normal_text(&input, &head, state);
	}
	return (expand_and_join(head, env, exit));
}

char	*expand_and_join(t_expand *head, t_env *env, int ex_status)
{
	char	*buffer;
	char	*tmp;

	buffer = NULL;
	while (head)
	{
		if (head->state == IN_DQUOTE && find_it(head->val, '$'))
		{
			tmp = heredoc_expander(head->val, env, ex_status);
			set_space_excep(tmp);
		}
		else if (head->state == NORMAL && find_it(head->val, '$'))
			tmp = heredoc_expander(head->val, env, ex_status);
		else
			tmp = ft_strdup(head->val);
		buffer = ft_strjoin(buffer, tmp);
		head = head->next;
	}
	return (buffer);
}

char	*expander(char *str, t_env *env, int exit)
{
	char	*expanded;

	if (!find_it(str, '$')
		&& !find_it(str, '\'')
		&& !find_it(str, '"'))
		return (str);
	expanded = handle_quotes(str, env, exit);
	return (expanded);
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

t_expand	*new_expand(t_state state, char *val)
{
	t_expand	*ret;

	ret = ft_malloc(sizeof(t_expand));
	ret->next = NULL;
	ret->state = state;
	ret->val = val;
	return (ret);
}
