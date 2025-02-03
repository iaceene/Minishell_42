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

static int ft_is_valid_identifier1(char *str)
{
    int i;

    if (!str || !str[0])
        return (0);
    i = 0;
    while (str[i])
    {
        if ('0' <= str[i] && str[i] <= '9' && i == 0)
            return (0);
        if (!(('0' <= str[i] && str[i] <= '9') || ('a' <= str[i] && str[i] <= 'z') || ('A' <= str[i] && str[i] <= 'Z') || str[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}

void builtin_unset(t_env **env, char **cmd_2d, int *exit_status)
{
    int i;
    int something_wrong;

    i = 1;
    something_wrong = 0;
    while (cmd_2d[i])
    {
        if (!(ft_is_valid_identifier1(cmd_2d[i])))
        {
            ft_print_err("unset: `");
            ft_print_err(cmd_2d[i]);
            ft_print_err("': not a valid identifier\n");
            something_wrong = 1;
        }
        else
            ft_env_delete(env, cmd_2d[i]);
        i++;
    }
    if (something_wrong)
        *exit_status = 1;
    else
        *exit_status = 0;
}
