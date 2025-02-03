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

static void ft_swap(t_env *node1, t_env *node2)
{
    char *tmp_value;
    char *tmp_key;

    tmp_key = node1->key;
    tmp_value = node1->value;
    node1->key = node2->key;
    node2->key = tmp_key;
    node1->value = node2->value;
    node2->value = tmp_value;
}

static void ft_print_sorted_env(t_env *env_dup)
{
    t_env *cur = env_dup;

    while (cur)
    {
        if (ft_strncmp(cur->key, "_", 1))
        {
            printf("declare -x %s", cur->key);
            if (cur->value && cur->visible)
                printf("=\"%s\"", cur->value);
            printf("\n");
        }
        cur = cur->next;
    }
}

static void ft_env_sort(t_env **env_dup)
{
    t_env *left = *env_dup;
    t_env *right;

    while (left && left->next)
    {
        right = left->next;
        while (right)
        {
            if (ft_strncmp(left->key, right->key, ft_strlen(right->key)) > 0)
                ft_swap(left, right);
            right = right->next;
        }
        left = left->next;
    }
}

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

void builtin_export(t_env **env, char **cmd_2d, int *exit_status)
{
    int i;
    t_env *env_dup;

    *exit_status = 0;
    if (!(cmd_2d[1]))
    {
        env_dup = ft_env_duplicate(*env);
        ft_env_sort(&env_dup);
        ft_print_sorted_env(env_dup);
        ft_env_clear(&env_dup);
        return;
    }
    i = 0;
    while (cmd_2d[++i])
        ft_export_help(cmd_2d[i], env, exit_status);
}
