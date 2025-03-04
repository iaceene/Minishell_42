/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 05:43:49 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/04 17:25:29 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

int pip_checker(t_node *data)
{
	t_node *prv;

	prv = NULL;
	while (data)
	{
		if (data->type == PIPE && (!prv || !data->next))
			return (0);
		if (data->type == PIPE
			&& (!valid_next(data->next->type)
			|| !valid_next(prv->type)))
			return (0);
		prv = data;
		data = data->next;
	}
	return (1);
}

int	readdir_checker(t_node *data)
{
	t_node *prv;

	prv = NULL;
	while (data)
	{
		// if (!prv && (data->type == LEFT_RED || data->type == RIGHT_RED))
		// 	return (0);
		if ((data->type == LEFT_RED || data->type == RIGHT_RED) && !data->next)
			return (0);
		if ((data->type == LEFT_RED || data->type == RIGHT_RED) &&
			!data->next && (data->next->type != COMMAND || prv->type != COMMAND))
			return (0);
		prv = data;
		data = data->next;
	}
	return (1);
}

int valid_parent(t_node *data)
{
	if (!data->next)
		return (1);
	if (data->type == OPEN_PAR && data->next->type == CLOSE_PAR)
		return (1);
	return (0);
}

int	syntax_checker(t_node *data)
{
	if (!data)
		return (-1);
	if (!pip_checker(data) || !readdir_checker(data) || !others_checker(data))
		return (-1);
	return (0);
}
