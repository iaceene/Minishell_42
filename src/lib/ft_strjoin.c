/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 22:05:56 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/31 18:08:45 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char    *ft_strjoin(char const *s1, char const *s2)
{
    int i = 0;
    int j = 0;
    if (!s1 || !s2)
        return (NULL);
    char *ret = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    while (s1[i])
    {
        ret[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        ret[i] = s2[j];
        j++;
        i++;
    }
    ret[i] = '\0';
    return (ret);
}