/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:18:10 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/09 00:10:25 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

int check_no_opned_pr(t_node *data)
{
	while (data)
	{
		if (data->type == CLOSE_PAR && data->visit == false)
			return (1);
		data = data->next;
	}
	return (0);
}

int	find_it(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

int	check_qoats(char *val)
{
	int	single;
	int	doubl;

	if (!find_it(val, '\'') && !find_it(val, '"'))
		return (0);
	single = 0;
	doubl = 0;
	while (*val)
	{
		if (*val == '\'')
			single++;
		if (*val == '"')
			doubl++;
		val++;
	}
	if (single % 2 != 0 ||
		doubl % 2 != 0)
		return (1);
	return(0);
}

int	check_herdoc(t_node *data)
{
	while (data)
	{
		if (data->type == HERDOC)
		{
			if (!data->next)
				return (1);
			if (data->next->type != COMMAND)
				return (0);
		}
		data = data->next;
	}
	return (0);
}


int others_checker(t_node *data)
{
	t_node	*tmp;

	tmp = data;
    while (data)
    {
		if (data->type == COMMAND)
			if (check_qoats(data->value))
				return (0);
        data = data->next;
    }
	if (check_no_opned_pr(tmp)
		|| check_herdoc(data))
		return (0);
    return (1);
}

int check_redirction(t_node *data)
{
	t_node *prv;

	prv = NULL;
	while (data)
	{
		if (data->type == RIGHT_RED || data->type == LEFT_RED)
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
