/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilse1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:24:36 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/18 06:24:36 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

void	ft_sort(t_cmd **head)
{
	t_cmd	*tmp;
	t_cmd	*last;
	t_cmd	*first_cmd;

	last = NULL;
	first_cmd = NULL;
	if (!head || !*head || (*head)->type == COMMAND)
		return ;
	tmp = *head;
	while (tmp && tmp->type != COMMAND)
	{
		last = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	first_cmd = tmp;
	if (last)
	{
		last->next = first_cmd->next;
		first_cmd->next = *head;
		*head = first_cmd;
	}
}
