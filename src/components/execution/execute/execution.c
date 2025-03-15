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

int ft_lstsize_head(t_exec *lst)
{
    if (!lst)
        return (0);
    int i = 0;
    while (lst)
    {
        i++;
        lst = lst->next;
    }
    return (i);
}

t_exec *copy_cmd_to_exec(t_cmd *cmd)
{
    t_exec *new_exec = NULL;
    t_exec *current_exec = NULL;

    while (cmd)
    {
        t_exec *new_node = malloc(sizeof(t_exec));
        if (!new_node)
            return NULL;

        new_node->type = cmd->type;
        new_node->value = ft_strdup(cmd->value);
        new_node->s = cmd->cmd;
        if (!new_node->value)
        {
            free(new_node);
            return NULL;
        }
        new_node->next = NULL;

        if (new_exec == NULL)
            new_exec = new_node;
        else
            current_exec->next = new_node;

        current_exec = new_node;
        cmd = cmd->next;
    }

    return new_exec;
}


void execution(t_cmd **head, t_env **env, int *exit_status)
{
    int cmd_count;
    t_exec *exec_list;

    if (!head || !*head)
        return;

    exec_list = copy_cmd_to_exec(*head);
    if (!exec_list)
    {
        perror("Failed to copy command list");
        return;
    }

    cmd_count = ft_lstsize_head(exec_list);

    if (cmd_count == 0)
    {
        while (exec_list)
        {
            t_exec *temp = exec_list;
            exec_list = exec_list->next;
            free(temp->value);
            free(temp);
        }
        return;
    }
    if (cmd_count == 1)
    {
        t_exec *cmd = exec_list;
        while (cmd && cmd->type != COMMAND)
            cmd = cmd->next;
        if (cmd)
            execution_cmd(cmd->value, env, exit_status);
    }
    else
        ft_pipex(exec_list, env, exit_status);

    while (exec_list)
    {
        t_exec *temp = exec_list;
        exec_list = exec_list->next;
        free(temp->value);
        free(temp);
    }
}
