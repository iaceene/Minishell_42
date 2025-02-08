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

void execution(t_cmd *head, t_env **env, int *exit_status)
{
    if (!head)
    {
        printf("Root is NULL\n");
        return;
    }

    t_cmd *current = head;
    int cmd_count = 0;
    t_cmd **commands = NULL;

    // Count commands and collect them
    while (current)
    {
        if (current->type != PIPE)
            cmd_count++;
        current = current->next;
    }

    if (cmd_count > 0)
    {
        commands = ft_malloc(sizeof(t_cmd *) * cmd_count);
        if (!commands)
            error_and_exit("Memory allocation failed", 1);

        current = head;
        int i = 0;
        while (current)
        {
            if (current->type != PIPE)
                commands[i++] = current;
            current = current->next;
        }
        if (cmd_count > 1)
            ft_pipex(commands, cmd_count, env, exit_status);
        // else if (commands[0]->type == APPEND || commands[0]->type == RIGHT_RED)
        // {
        //     printf("Executing redirection\n");
        //     ft_execute_redirection_out(commands[0], env, exit_status);
        // }
        // else if (commands[0]->type == LEFT_RED)
        // {
        //     printf("Executing redirection\n");
        //         ft_execute_redirection_in(commands[0], env, exit_status);
        // }
        // else if (commands[0]->type == HERDOC)
        // {
        //     printf("Executing heredoc\n");
        //     ft_execute_heredoc(commands[0], env, exit_status);
        // }
        else
		{
			printf("Executing single\n");
            execution_cmd(commands[0]->value, env, exit_status);
		}

        free(commands);
    }
}
