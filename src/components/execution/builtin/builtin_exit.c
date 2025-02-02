/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:07:33 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/27 13:06:06 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void builtin_exit(char **args)
{
    int exit_code = 0;

    if (args[1])
    {
        int i;

        i = 0;
        while (args[1][i])
        {
            if (!ft_isdigit(args[1][i]))
                error_and_exit("exit: numeric argument required\n", 255);
            i++;
        }
        exit_code = ft_atoi(args[1]);
    }

    exit(exit_code);
}
