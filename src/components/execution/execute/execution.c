/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:23:52 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/26 16:51:29 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"
#include "../../../../include/minishell.h"
#include "../../../../include/parser.h"

void	execution(t_cmd *head, t_env **env, int *exit_status)
{
	(void)env;
	(void)exit_status;
	// (void)root;
	// if (!root)
	// {
	// 	printf("Root is NULL\n");
	// 	return ;
	// }
	// else if (root->type == PIPE)
	// 	ft_execute_pipe(root, env, exit_status);
	// else if (root->type == REDIRECTION || root->type == APPEND_REDIRECTION)
	// 	ft_execute_redirection_out(root, env, exit_status);
	// else if (root->type == INPUT || root->type == HERE_DOC)
	// 	ft_execute_redirection_in(root, env, exit_status);
	// else
	// if ()
	// 	printf("Root value: %s\n", root->head->value);
	// else
	// 	printf("Root value: NULL\n");	

	while (head)
	{
		if (head->type == COMMAND)
			execution_cmd(head->value, env, exit_status);
		head = head->next;
	}
}
