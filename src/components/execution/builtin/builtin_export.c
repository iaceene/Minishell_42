/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:44:54 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/27 13:04:06 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

void ft_export_error(char *slice1, char *slice2, int equal, int append)
{
    ft_print_err("export: `");
    ft_print_err(slice1);
    if (equal)
        ft_print_err("=");
    else if (append == 1)
        ft_print_err("+");
    ft_print_err(slice2);
    ft_print_err("': not a valid identifier\n");
}
static t_env *sorted_merge(t_env *a, t_env *b)
{
    t_env *result = NULL;

    if (!a)
        return b;
    if (!b)
        return a;

    if (strcmp(a->key, b->key) <= 0)
    {
        result = a;
        result->next = sorted_merge(a->next, b);
    }
    else
    {
        result = b;
        result->next = sorted_merge(a, b->next);
    }
    return result;
}

static void front_back_split(t_env *source, t_env **front_ref, t_env **back_ref)
{
    t_env *fast;
    t_env *slow;
    slow = source;
    fast = source->next;

    while (fast)
    {
        fast = fast->next;
        if (fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front_ref = source;
    *back_ref = slow->next;
    slow->next = NULL;
}

void ft_env_sort(t_env **head_ref)
{
    t_env *head = *head_ref;
    t_env *a;
    t_env *b;

    if (!head || !head->next)
        return;

    front_back_split(head, &a, &b);

    ft_env_sort(&a);
    ft_env_sort(&b);

    *head_ref = sorted_merge(a, b);
}

static void ft_print_sorted_env(t_env *env)
{
    t_env *cur = env;
    while (cur)
    {
        if (strcmp(cur->key, "_") != 0)
        {
            printf("declare -x %s", cur->key);
            if (cur->value && cur->visible)
                printf("=\"%s\"", cur->value);
            printf("\n");
        }
        cur = cur->next;
    }
}

void builtin_export(t_env **env, char **cmd_2d, int *exit_status)
{
    int i;
    t_env *env_dup;

    *exit_status = 0;
    if (!cmd_2d[1])
    {
        env_dup = ft_env_duplicate(*env);
        ft_env_sort(&env_dup);
        ft_print_sorted_env(env_dup);
        ft_env_clear(&env_dup);
    }
    i = 0;
    while (cmd_2d[++i])
        ft_export_help(cmd_2d[i], env, exit_status);
}
