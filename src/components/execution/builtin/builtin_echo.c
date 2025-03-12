/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:54:22 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/27 13:05:00 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static int check_falg(char *flag)
{
    int i;

    if (flag[0] != '-' || !flag[1])
        return (0);
    i = 1;
    while (flag[i])
    {
        if (flag[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

void builtin_echo(char **arg)
{
    int i;
    int flag_n;

    flag_n = 1;
    i = 1; 
    while (arg[i] && check_falg(arg[i]))
    {
        flag_n = 0;
        i++;
    }
    while (arg[i])
    {
        printf("%s", arg[i++]);
        if (arg[i])
            printf(" ");
    }
    if (flag_n)
        printf("\n");
}
