/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_adv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:22:16 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/20 18:39:47 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

void	set_back_space(char *val)
{
	if (!val)
		return ;
	while (*val)
	{
		if (*val == -1)
			*val = ' ';
		val++;
	}
}

static int	ft_isspliter(char c)
{
	return (ft_isspace(c));
}

static int	ft_count(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		while (str[i] && ft_isspliter(str[i]))
			i++;
		if (str[i])
			c++;
		while (str[i] && !ft_isspliter(str[i]))
			i++;
	}
	return (c);
}

static char	*ft_allocate(char *str, int *index)
{
	int		i;
	int		saved_index;
	char	*splited;

	i = 0;
	saved_index = *index;
	while (str[saved_index] && !ft_isspliter(str[saved_index]))
	{
		saved_index++;
		i++;
	}
	splited = ft_malloc(i + 1);
	splited[i] = '\0';
	i = 0;
	while (str[*index] && !ft_isspliter(str[*index]))
	{
		splited[i] = str[*index];
		(*index)++;
		i++;
	}
	return (splited);
}

char	**ft_split_adv(char const *s)
{
	char	**splites;
	int		count_spiltes;
	int		i;
	int		index;

	if (!s || !*s)
		return (NULL);
	i = 0;
	index = 0;
	count_spiltes = ft_count((char *)s);
	splites = ft_malloc(sizeof(char *) * (count_spiltes + 1));
	splites[count_spiltes] = NULL;
	while (i < count_spiltes)
	{
		while (s[index] && ft_isspliter(s[index]))
			index++;
		splites[i] = ft_allocate((char *)s, &index);
		i++;
	}
	return (splites);
}
