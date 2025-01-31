/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:25:25 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/31 18:08:18 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ft_strdup(const char *s)
{
    int i = 0;
	if (!s || !*s)
		return (NULL);
    char *ret = ft_malloc(ft_strlen(s) + 1);
    while (s[i])
    {
        ret[i] = s[i]; 
        i++;
    }
    ret[i] = '\0';
    return (ret);
}
