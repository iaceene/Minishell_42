/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_step.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 02:19:08 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/16 22:53:58 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

t_cmd	*new_cmd(t_node *node)
{
	t_cmd	*ret;

	ret = ft_malloc(sizeof(t_cmd));
	if (!node)
	{
		ret->type = NIL;
		ret->value = NULL;
		ret->next = NULL;
		return (ret);
	}
	if (node->type == HERDOC)
	{
		ret->fd_herdoc = node->hr_fd;
		printf("hedoc fd %d\n", ret->fd_herdoc);
	}
	ret->type = node->type;
	ret->value = node->value;
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

t_cmd	*data_maker(t_node *head, t_env *env)
{
	t_cmd	*cmd;

	if (!head)
		return (NULL);
	cmd = NULL;
	while (head)
	{
		if (head->type == COMMAND)
		{
			head->value = expander(head, env);
			add_to_cmd(&cmd, new_cmd(head));
		}
		else if (head->type == HERDOC && head->next)
		{
			head->hr_fd = herdoc(env, head->next->value);
			add_to_cmd(&cmd, new_cmd(head));
			head = head->next;
		}
		else
			add_to_cmd(&cmd, new_cmd(head));
		head = head->next;
	}
	return (cmd);
}
