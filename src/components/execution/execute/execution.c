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
void change_redirections_and_delete_pipe(t_exec **exec_list)
{
    t_exec *current = *exec_list;
    t_exec *prev = NULL;

    while (current)
    {
        if (current->type == PIPE)
        {
            t_exec *temp = current;
            if (prev)
                prev->next = current->next;
            else
                *exec_list = current->next;
            current = current->next;
            free(temp->value);
            free(temp);
        }
        else if (current->type == HERDOC || current->type == RIGHT_RED || current->type == LEFT_RED)
        {
            if (current->next)
            {
                if (current->type == RIGHT_RED)
                    current->next->type = OUTFILE;
                else if (current->type == LEFT_RED)
                    current->next->type = INFILE;
                else if (current->type == HERDOC)
                    current->next->type = HEREDOC_FILE;
                else if (current->type == APPEND)
                    current->next->type = APPEND_FILE;
                t_exec *temp = current;
                if (prev)
                    prev->next = current->next;
                current = current->next;
                free(temp->value);
                free(temp);
            }
            else
            {
                prev = current;
                current = current->next;
            }
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
}

void execution(t_cmd **head, t_env **env, int *exit_status)
{
    if (!head || !*head)
        return;

    t_exec *exec_list = copy_cmd_to_exec(*head);

    change_redirections_and_delete_pipe(&exec_list);

    // while (exec_list)
    // {
    //     fprintf(stderr, "exec_list->value: %s => ", exec_list->value);
    //     fprintf(stderr, "exec_list->type: %d\n", exec_list->type);
    //     exec_list = exec_list->next;
    // }
    int cmd_count = ft_lstsize_head(exec_list);
    if (cmd_count == 0)
        return;
    // printf("cmd_count: %d\n", cmd_count);

    if (cmd_count == 1)
        execution_cmd(exec_list->value, env, exit_status);
    else
        ft_pipex(exec_list, cmd_count, env, exit_status);
}
