/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:45:27 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/31 17:26:16 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcheck(char *str, char *word, size_t index)
{
	size_t	i;

	i = 0;
	while (word[i] && str[index + i] == word[i])
		i++;
	return (word[i] == '\0');
}

char	*ft_strstr(char *haystack, char *needle)
{
	size_t	i;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			if (ft_strcheck(haystack, needle, i))
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
