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


#include "../../../../include/minishell.h"

int ft_lstsize_cmd(t_cmd *lst)
{
    int i = 0;
    while (lst)
    {
        i++;
        lst = lst->next;
    }
    return (i);
}
void execution(t_cmd *head, t_env **env, int *exit_status)
{
    if (!head)
        return;

    int cmd_count = ft_lstsize_cmd(head);
    if (cmd_count == 0)
        return;

    t_cmd **commands = ft_malloc(sizeof(t_cmd *) * (cmd_count + 1));
    if (!commands)
        error_and_exit("Memory allocation failed", 1);

    t_cmd *cmd = head;
    int i = 0;
    int j = 0;

    while (cmd)
    {
        if (cmd->type == RIGHT_RED || cmd->type == APPEND || cmd->type == LEFT_RED || cmd->type == HERDOC)
        {
            if (cmd->next)
                cmd->next->type = FILENAME;
            commands[i++] = cmd;
        }
        else if (cmd->type != PIPE)
        {
            commands[i++] = cmd;
            j++;
        }
        cmd = cmd->next;
    }
    commands[i] = NULL;
    // int j = 0;
    // while (commands[j])
    // {
    //     printf("command: {%s}", commands[j]->value);
    //     printf("type: %d\n", commands[j]->type);
    //     j++;
    // }

    // printf("cmd_count: %d\n", i);  // Debugging output

    printf("number commands: %d\n", i);
    if (i == 1)
        execution_cmd(commands[0]->value, env, exit_status);
    else
        ft_pipex(commands, i, env, exit_status);
    (void)exit_status;
    (void)env;
    free(commands);
}
