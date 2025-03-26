/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_step.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 02:19:08 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/26 03:15:33 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

t_cmd	*new_cmd(t_node *node)
{
	t_cmd	*ret;

	ret = ft_malloc(sizeof(t_cmd));
	if (!node)
	{
		ret->pip_infront = false;
		ret->type = NIL;
		ret->value = NULL;
		ret->next = NULL;
		ret->cmd = NULL;
		return (ret);
	}
	if (node->type == HERDOC)
		ret->fd_herdoc = node->hr_fd;
	ret->pip_infront = false;
	ret->type = node->type;
	ret->value = node->value;
	ret->cmd = NULL;
	ret->next = NULL;
	return (ret);
}

void	add_to_cmd(t_cmd **head, t_cmd *new)
{
	t_cmd	*last;

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

t_cmd	*data_maker(t_node *head, t_env *env, int exit)
{
	t_cmd	*cmd;

	if (!head)
		return (NULL);
	cmd = NULL;
	while (head)
	{
		if (head->type == COMMAND)
		{
			head->value = expander(head->value, env, exit);
			add_to_cmd(&cmd, new_cmd(head));
		}
		else if (head->type == HERDOC)
		{
			head->value = head->next->value;
			add_to_cmd(&cmd, new_cmd(head));
			head = head->next;
		}
		else
			add_to_cmd(&cmd, new_cmd(head));
		head = head->next;
	}
	return (cmd);
}

char	*handle_qoa_cmd(char *s, int *in_quotes, char *quote_char)
{
	while (*s && (*in_quotes || !operator(*s)))
	{
		if ((*s == '\'' || *s == '"') && !(*in_quotes))
		{
			*in_quotes = 1;
			*quote_char = *s;
		}
		else if (*s == *quote_char && *in_quotes)
		{
			*in_quotes = 0;
			*quote_char = 0;
		}
		s++;
	}
	return (s);
}
