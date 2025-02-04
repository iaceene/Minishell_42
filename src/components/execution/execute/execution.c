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

void	execution(t_tree *root, t_env **env, int *exit_status)
{
	if (!root)
	{
		printf("Root is NULL\n");
		return ;
	}
	// else if (root->type == PIPE)
	// 	ft_execute_pipe(root, env, exit_status);
	// else if (root->type == REDIRECTION || root->type == APPEND_REDIRECTION)
	// 	ft_execute_redirection_out(root, env, exit_status);
	// else if (root->type == INPUT || root->type == HERE_DOC)
	// 	ft_execute_redirection_in(root, env, exit_status);
	// else
		execution_cmd(root->value, env, exit_status);
}
