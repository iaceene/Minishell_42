/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 01:57:06 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/30 22:52:39 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_join(char *s1, char *s2)
{
	int		len;
	char	*ret;
	int		j;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s2 && s1)
		return (s1);
	len = ft_strlen(s1) + ft_strlen(s2);
	ret = ft_malloc(len + 1);
	i = -1;
	while (s1[++i])
		ret[i] = s1[i];
	j = 0;
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (ret);
}

char	*ft_sub_helper(char *s, char *ret, int line, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		ret[j] = s[j];
		j++;
	}
	if (line)
	{
		ret[i] = '\n';
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_sub(char *s)
{
	char	*ret;
	int		i;
	int		new_line;
	int		j;

	if (!s || !*s)
		return (NULL);
	i = 0;
	j = 1;
	new_line = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
	{
		new_line = 1;
		j = 2;
	}
	ret = ft_malloc(i + j);
	return (ft_sub_helper(s, ret, new_line, i));
}
