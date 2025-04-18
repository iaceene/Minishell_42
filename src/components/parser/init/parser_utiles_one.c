/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utiles_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:38:23 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/26 20:38:43 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

void	close_fds(t_cmd *head)
{
	while (head)
	{
		if (head->type == HERDOC && head->fd_herdoc != -1)
			close(head->fd_herdoc);
		head = head->next;
	}
}

t_cmd	*get_last_cmd(t_cmd *head)
{
	t_cmd	*last;

	if (!head)
		return (NULL);
	if (head->type == COMMAND)
		last = head;
	else
		last = NULL;
	while (head)
	{
		if (head->type == COMMAND)
			last = head;
		head = head->next;
	}
	return (last);
}

t_cmd	*get_last_cmd_pip(t_cmd *head)
{
	t_cmd	*last;

	if (!head)
		return (NULL);
	if (head->type == COMMAND)
		last = head;
	else
		last = NULL;
	while (head)
	{
		if (head->type == COMMAND)
			last = head;
		head = head->next;
	}
	if (last && last->pip_infront)
		return (NULL);
	return (last);
}
