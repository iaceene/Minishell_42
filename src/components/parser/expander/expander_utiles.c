/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 23:58:48 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/09 08:40:23 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

char *ft_strndup(char *s, size_t n)
{
	char		*ret;
	size_t		i;
	
	i = 0;
	if (!s)
		return (NULL);
	if (!*s && n == 0)
		return (ft_strdup(""));
	ret = ft_malloc(n + 1);
	while (i < n)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}