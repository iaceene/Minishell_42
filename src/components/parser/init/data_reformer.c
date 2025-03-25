/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_reformer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:01:59 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/25 21:18:48 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

void	insert_cmd_before_redirs(t_cmd **head, t_cmd *cmd, t_cmd *redir)
{
	t_cmd	*before_redir;

	if (redir == *head)
	{
		cmd->next = redir;
		*head = cmd;
	}
	else
	{
		before_redir = *head;
		while (before_redir->next != redir)
			before_redir = before_redir->next;
		before_redir->next = cmd;
		cmd->next = redir;
	}
}

void	reforme_data(t_cmd **head)
{
	t_cmd	*current;
	t_cmd	*prev;
	t_cmd	*first_redir;
	t_cmd	*cmd_node;

	current = *head;
	prev = NULL;
	first_redir = NULL;
	while (current != NULL)
	{
		if (current->type == IN_FILE || current->type == OUT_FILE)
		{
			if (first_redir == NULL)
				first_redir = current;
		}
		else if (current->type == COMMAND && first_redir != NULL)
		{
			cmd_node = current;
			if (prev != NULL)
				prev->next = cmd_node->next;
			else
				*head = cmd_node->next;
			insert_cmd_before_redirs(head, cmd_node, first_redir);
			first_redir = NULL;
			current = cmd_node;
		}
		else
			first_redir = NULL;
		prev = current;
		current = current->next;
	}
}
