/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utiles_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:38:23 by iezzam            #+#    #+#             */
/*   Updated: 2025/04/19 18:18:51 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

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
