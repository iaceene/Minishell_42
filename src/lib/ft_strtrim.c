/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:45:03 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/31 18:08:58 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_spliter(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	start;
	size_t	index;
	char	*trimed;
	size_t	len;

	if ((!s1 && !set) || !s1)
		return (NULL);
	if (s1 && !set)
		return (ft_strdup(s1));
	start = 0;
	index = 0;
	len = ft_strlen(s1);
	while (s1[start] && ft_spliter(s1[start], set))
		start++;
	while (len > start && ft_spliter(s1[len - 1], set))
		len--;
	trimed = ft_malloc(len - start + 1);
	while (start < len)
		trimed[index++] = s1[start++];
	trimed[index] = '\0';
	return (trimed);
}
