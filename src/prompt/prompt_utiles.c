/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:44:11 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/30 19:47:12 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *ft_strchr(char *s, char c)
{
    int i = 0;
    while (s[i])
    {
        if (c == s[i])
            return (s + i);
        i++;
    }
    return (NULL);
}

char *ft_join_params(char *user, char *sep, char *dis, char *dock)
{
    if (!user || !sep || !dis)
        return (exit(1), NULL);
    int i = 0;
    char *cli = ft_malloc (ft_strlen(user) + ft_strlen(sep) + ft_strlen(dis) + ft_strlen(dock) + 1);
    while (user[i])
    {
        cli[i] = user[i];
        i++;
    }
    int j = 0;
    while (sep[j])
    {
        cli[i] = sep[j];
        i++;
        j++;
    }
    j = 0;
    while (dis[j])
    {
        cli[i] = dis[j];
        i++;
        j++;
    }
    j = 0;
    while (dock[j])
    {
        cli[i] = dock[j];
        i++;
        j++;
    }
    cli[i] = '\0';
    return (cli);
}
