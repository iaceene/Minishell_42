/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:47:19 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/27 13:03:42 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

static int is_valid_env_name(char *name)
{
    int index;

    if (!name || !name[0])
        return (0);
    index = 0;
    while (name[index])
    {
        if ('0' <= name[index] && name[index] <= '9' && index == 0)
            return (0);
        if (!(('0' <= name[index] && name[index] <= '9') || ('a' <= name[index] && name[index] <= 'z') || ('A' <= name[index] && name[index] <= 'Z') || name[index] == '_'))
            return (0);
        index++;
    }
    return (1);
}

void builtin_unset(t_env **env, char **arg, int *exit_status)
{
    int index;
    int invalid_flag;

    index = 1;
    invalid_flag = 0;
    while (arg[index])
    {
        if (!(is_valid_env_name(arg[index])))
        {
            ft_print_err("unset error: `");
            ft_print_err(arg[index]);
            ft_print_err("': invalid identifier\n");
            invalid_flag = 1;
        }
        else
            ft_env_delete(env, arg[index]);
        index++;
    }
    if (invalid_flag)
        *exit_status = 1;
    else
        *exit_status = 0;
}
