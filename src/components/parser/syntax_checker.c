/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 05:43:49 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/03 19:44:27 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parser.h"


int search_for_acc (TokenType type, t_node *head)
{
	if (!head)
		return (1);
	while (head)
	{
		if (head->type == type && head->flaged == 0)
		{
			head->flaged = 1;
			return (0);
		}
		head = head->next;
	}
	return (1);
}

int	syntax_checker(t_node *data)
{
	t_node *temp = data;
    while (temp)
	{
        printf("Token: %s, Type: %d\n", temp->value, temp->type);
        temp = temp->next;
    }

	while (data)
	{
		if (data->type == SIN_QUOTE && data->flaged == 0)
			if (search_for_acc(SIN_QUOTE, data->next))
				return (-1);
		if (data->type == DOB_QUOTE && data->flaged == 0)
			if (search_for_acc(DOB_QUOTE, data->next))
				return (-1);
		if (data->type == OPEN_PAR && data->flaged == 0)
			if (search_for_acc(CLOSE_PAR, data->next))
				return (-1);
		if (data->type == CLOSE_PAR && data->flaged == 0)
			return (-1);
		data = data->next;
	}
	return (0);
}
