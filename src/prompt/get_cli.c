/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cli.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:42:28 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/30 22:14:46 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *ft_get_user(char **env)
{
    int i = 0;
    int flag = 0;
    while (env[i])
    {
        if (ft_strstr(env[i], "LOGNAME"))
        {
            flag = 1;
            break ;
        }
        i++;
    }
    if (flag == 0)
        return (NULL);
    return (ft_strdup(ft_strchr(env[i], '=') + 1));
}

char *ft_get_sission(char **env)
{
    int i = 0;
    int flag = 0;
    while (env[i])
    {
        if (ft_strstr(env[i], "SESSION_MANAGER"))
        {
            flag = 1;
            break ;
        }
        i++;
    }
    if (flag == 0)
        return (NULL);
    return (ft_strdup(ft_strtrim(ft_strchr(env[i], '/') + 1, '.')));
}

char *ft_get_cli(char **env)
{
    char *user;
    char *desktop;
    char *cli;

    user = ft_get_user(env);
    if (!user)
        user = ft_strdup("user42");
    desktop = ft_get_sission(env);
    if (!desktop)
        desktop = ft_strdup("1337");
    cli = ft_join_params(user, "@", desktop, ">> ");
    return (cli);
}