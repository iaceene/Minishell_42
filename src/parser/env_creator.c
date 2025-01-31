/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:35:49 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/31 13:52:17 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list *new_env_var(char *var)
{
    t_list *new;

    new = ft_malloc(sizeof(t_list));
    new->val = var;
    new->next = NULL;
    return (new);
}

t_list *last_var(t_list *head)
{
    while (head && head->next)
        head = head->next;
    return (head);
}

void add_new_env(t_list **head, t_list *new)
{
    t_list *last;

    if (!head)
        return ;
    if (!*head)
    {
        *head = new;
        return ;
    }
    else
    {
        last = last_var(*head);
        last->next = new;
        return ;  
    }
}

t_list *env_creator(char **env)
{
    int i;
    t_list *env_var;

    i = 0;
    env_var = NULL;
    while (env[i])
    {
        add_new_env(&env_var, new_env_var(ft_strdup(env[i])));
        i++;
    }
    return (env_var);
}
