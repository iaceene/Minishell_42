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

#include "../../../../include/minishell.h"

void builtin_export(char **args, char ***env)
{
    if (!args[1])
    {
        int i;

        i = 0;
        while ((*env)[i])
        {
            write(1, (*env)[i], ft_strlen((*env)[i]));
            write(1, "\n", 1);
            i++;
        }
        return;
    }

    char *var = ft_strdup(args[1]);
    char *equal_sign = ft_strchr(var, '=');
    if (!equal_sign)
    {
        write(2, "export: invalid argument\n", 25);
        free(var);
        return;
    }

    *equal_sign = '\0';
    char *key = var;
    char *value = equal_sign + 1;

    int i = 0;
    while ((*env)[i])
    {
        if (ft_strncmp((*env)[i], key, ft_strlen(key)) == 0 && (*env)[i][ft_strlen(key)] == '=')
        {
            free((*env)[i]);
            (*env)[i] = ft_strdup(args[1]);
            free(var);
            return;
        }
        i++;
    }

    int count = 0;
    while ((*env)[count])
        count++;
    *env = realloc(*env, sizeof(char *) * (count + 2));
    (*env)[count] = ft_strdup(args[1]);
    (*env)[count + 1] = NULL;
    free(var);
}
