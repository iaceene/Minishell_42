/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 05:43:49 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/05 20:15:31 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parser.h"

void print_data(t_node *data)
{
	t_node *temp = data;
	if (!data)
		printf("\nNIL\n");;
    while (temp)
	{
        printf("Token: %s, Type: ", temp->value);
		if (temp->type == COMMAND)
			printf("command");
		if (temp->type == PIPE)
			printf("pipe");
		if (temp->type == APPEND)
			printf("append");
		if (temp->type == HERDOC)
			printf("herdoc");
		if (temp->type == RIGHT_RED)
			printf("right redirection");
		if (temp->type == LEFT_RED)
			printf("left redirection");
		if (temp->type == SIN_QUOTE)
			printf("single quate");
		if (temp->type == DOB_QUOTE)
			printf("double quate");
		if (temp->type == DOLLAR)
			printf("dolar");
		if (temp->type == OPEN_PAR)
			printf("open parenthesis");
		if (temp->type == CLOSE_PAR)
			printf("close parenthesis");
		printf("\n");
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
			if (data->next->type != COMMAND || prv->type != COMMAND)
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


int	syntax_checker(t_node *data)
{
	// print_data(data);
	if (check_pip(data) || check_append(data)
		|| check_redirction(data))
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
			if (data->next != COMMAND || search_for_acc(CLOSE_PAR, data->next))
				return (-1);
		if (data->type == CLOSE_PAR && data->flaged == 0)
			return (-1);
		data = data->next;
	}
	return (0);
}
