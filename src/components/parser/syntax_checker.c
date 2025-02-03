/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 05:43:49 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/03 20:17:36 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parser.h"

void print_data(t_node *data)
{
	t_node *temp = data;
    while (temp)
	{
        printf("Token: %s, Type: %d\n", temp->value, temp->type);
        temp = temp->next;
    }
}

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

int check_pip(t_node *data)
{
	t_node *prv;

	prv = NULL;
	while (data)
	{
		if (data->type == PIPE)
		{
			if (!prv)
				return (1);
			if (!data->next)
				return (1);
			if (data->next->type != WORD || prv->type != WORD)
				return (1);
		}
		prv = data;	
		data = data->next;
	}
	return (0);
}

int check_append(t_node *data)
{
	t_node *prv;

	prv = NULL;
	while (data)
	{
		if (data->type == LEFT_APP)
		{
			if (!prv)
				return (1);
			if (!data->next)
				return (1);
			if (data->next->type != WORD || prv->type != WORD)
				return (1);
		}
		prv = data;	
		data = data->next;
	}
	return (0);
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
			if (data->next->type != WORD || prv->type != WORD)
				return (1);
		}
		prv = data;	
		data = data->next;
	}
	return (0);
}

int check_logical(t_node *data)
{
	t_node *prv;

	prv = NULL;
	while (data)
	{
		if (data->type == AND || data->type == OR)
		{
			if (!prv)
				return (1);
			if (!data->next)
				return (1);
			if (data->next->type != WORD || prv->type != WORD)
				return (1);
		}
		prv = data;	
		data = data->next;
	}
	return (0);
}

int	syntax_checker(t_node *data)
{
	print_data(data);
	if (check_pip(data) || check_append(data)
		|| check_redirction(data) || check_logical(data))
		return (-1);
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
