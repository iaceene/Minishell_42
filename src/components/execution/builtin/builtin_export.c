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

void print_export_error(char *part1, char *part2, int has_equal, int has_append)
{
    ft_print_err("export error: `");
    ft_print_err(part1);
    if (has_equal)
        ft_print_err("=");
    else if (has_append == 1)
        ft_print_err("+");
    ft_print_err(part2);
    ft_print_err("': invalid identifier\n");
}

static t_env *merge_sorted_env(t_env *a, t_env *b)
{
    t_env *result = NULL;

    if (!a)
        return b;
    if (!b)
        return a;

    if (strcmp(a->key, b->key) <= 0)
    {
        result = a;
        result->next = merge_sorted_env(a->next, b);
    }
    else
    {
        result = b;
        result->next = merge_sorted_env(a, b->next);
    }
    return result;
}

static void split_env_list(t_env *source, t_env **front_ref, t_env **back_ref)
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

void sort_env_list(t_env **head_ref)
{
    t_env *head = *head_ref;
    t_env *a;
    t_env *b;

    if (!head || !head->next)
        return;

    split_env_list(head, &a, &b);

    sort_env_list(&a);
    sort_env_list(&b);

    *head_ref = merge_sorted_env(a, b);
}

static void print_sorted_env(t_env *env)
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

void builtin_export(t_env **env, char **cmd_args, int *exit_status)
{
    int i;
    t_env *env_dup;

    *exit_status = 0;
    if (!cmd_args[1])
    {
        env_dup = ft_env_duplicate(*env);
        sort_env_list(&env_dup);
        print_sorted_env(env_dup);
        ft_env_clear(&env_dup);
    }
    i = 0;
    while (cmd_args[++i])
        ft_export_help(cmd_args[i], env, exit_status);
}
