/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:45:27 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/30 23:44:44 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_strlen(char *s)
{
    int i = 0;
	if (!s)
		return (0);
    while (s[i])
    {
        i++;
    }
    return (i);
}

char *ft_strdup(char *s)
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

int	ft_strcheck(char *str, char *word, size_t index)
{
	size_t	i;
	size_t	word_len;

	word_len = ft_strlen(word);
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
