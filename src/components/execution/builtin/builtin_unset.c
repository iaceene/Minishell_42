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

#include "../../../../include/minishell.h"

void builtin_unset(char **args, char ***env)
{
    if (!args[1])
    {
        write(2, "unset: missing argument\n", 24);
        return;
    }
    int i = 0;

    while ((*env)[i])
    {
        if (ft_strncmp((*env)[i], args[1], ft_strlen(args[1])) == 0 && (*env)[i][ft_strlen(args[1])] == '=')
        {
            free((*env)[i]);
            int j = i;
            while ((*env)[j])
            {
                (*env)[j] = (*env)[j + 1];
                j++;
            }
            return;
        }
        i++;
    }
}
