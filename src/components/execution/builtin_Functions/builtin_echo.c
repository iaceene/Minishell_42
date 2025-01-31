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


void builtin_echo(char **args)
{
    int newline = 1;
    int i = 1;

    if (args[1] && ft_strncmp(args[1], "-n", 2) == 0)
    {
        newline = 0;
        i = 2;
    }

    while (args[i])
    {
        write(1, args[i], ft_strlen(args[i]));
        if (args[i + 1])
            write(1, " ", 1);
        i++;
    }

    if (newline)
        write(1, "\n", 1);
}