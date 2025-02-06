/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 05:43:49 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/06 15:54:42 by yaajagro         ###   ########.fr       */
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
			printf("single quate FLAGE = %d", data->flaged);
		if (temp->type == DOB_QUOTE)
			printf("double quate FLAGE = %d", data->flaged);
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

int	search_for_acc(TokenType type, t_node *head)
{
	while (head)
	{
		if (head->type == type && head->flaged == 0)
		{
			head->flaged = 1;
			return 0;
		}
		head = head->next;
	}
	return 1;
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


int pip_checker(t_node *data)
{
	t_node *prv;

	prv = NULL;
	while (data)
	{
		if (data->type == PIPE && !prv)
			return (0);
		if (data->type == PIPE && !data->next)
			return (0);
		if (data->type == PIPE &&
			(data->next->type != COMMAND || prv->type != COMMAND))
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
		if ((data->type == LEFT_RED || data->type == RIGHT_RED) && (data->next->type != COMMAND || prv->type != COMMAND))
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

int check_no_opned_pr(t_node *data)
{
	while (data)
	{
		if (data->type == CLOSE_PAR && data->flaged == 0)
			return (1);
		data = data->next;
	}
	return (0);
}

int others_checker(t_node *data)
{
    if (!data)
        return 1;
    while (data)
    {
        if ((data->type == SIN_QUOTE || data->type == DOB_QUOTE) && data->flaged == 0)
        {
            if (search_for_acc(data->type, data->next))
                return 0;
        }
        if (data->type == OPEN_PAR)
        {
            if (search_for_acc(CLOSE_PAR, data->next) || valid_parent(data))
                return 0;
        }
        if ((data->type == APPEND || data->type == RIGHT_RED) && !data->next)
            return 0;

        data = data->next;
    }

    return 1;
}

int	syntax_checker(t_node *data)
{
	print_data (data);
	if (!pip_checker(data) || !readdir_checker(data) || !others_checker(data))
		return (-1);
	return (0);
}
