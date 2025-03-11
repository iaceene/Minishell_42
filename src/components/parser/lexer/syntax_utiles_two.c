/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utiles_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:23:16 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/11 23:09:24 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

int	check_no_opned_pr(t_node *data)
{
	while (data)
	{
		if (data->type == CLOSE_PAR && data->visit == false)
			return (1);
		data = data->next;
	}
	return (0);
}

int	valid_next(TokenType type)
{
	return (type == COMMAND);
}

int	check_append(t_node *data)
{
	t_node	*prv;

	prv = NULL;
	while (data)
	{
		if (data->type == HERDOC)
		{
			if (!prv)
				return (1);
			if (!data->next)
				return (1);
			if (data->next->type != COMMAND || prv->type != COMMAND)
				return (1);
		}
		prv = data;
		data = data->next;
	}
	return (0);
}
