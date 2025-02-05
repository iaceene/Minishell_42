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

static int ft_echo_valid_flag(char *flag)
{
    int i;

    if (flag[0] != '-')
        return (0);
    i = 1;
    if (!flag[i])
        return (0);
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
    printf("yse echo\n");
    int i;
    int print_nl;

    print_nl = 1;
    i = 1;
    while (arg[i] && ft_echo_valid_flag(arg[i]))
    {
        print_nl = 0;
        i++;
    }
    while (arg[i])
    {
        printf("%s", arg[i++]);
        if (arg[i])
            printf(" ");
    }
    if (print_nl)
        printf("\n");
}
