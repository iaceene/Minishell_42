/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utiles_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:25:08 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/11 20:57:23 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

int	is_sperator(char c)
{
	return (c == '-' || c == ' ' || c == '\t'
		|| c == '\'' || c == '"' || c == '$'
		|| c == ']' || c == '[' || c == -1
		|| c == -2);
}

char	*get_before(char *s)
{
	char	*ret;
	int		i;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	ret = ft_malloc(i + 1);
	i = 0;
	while (s[i] && s[i] != '$')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*get_after(char *s)
{
	char	*ret;
	int		i;
	int		len;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	if (s[i] == '$')
	{
		i++;
		while (s[i] && !is_sperator(s[i]))
			i++;
	}
	len = ft_strlen(s + i);
	ret = ft_malloc(len + 1);
	len = 0;
	while (s[i])
	{
		ret[len] = s[i];
		i++;
		len++;
	}
	ret[len] = '\0';
	return (ret);
}

char	*extract_name(char *str)
{
	int		i;
	int		start;
	char	*ret;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (!str[i + 1] || is_sperator(str[i + 1]))
		return (NULL);
	start = i + 1;
	i = start;
	while (str[i] && !is_sperator(str[i]))
		i++;
	ret = ft_malloc(i - start + 1);
	i = 0;
	while (str[start] && !is_sperator(str[start]))
	{
		ret[i] = str[start];
		start++;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	set_empty_str(char **s)
{
	int		i;
	int		j;
	bool	f;

	if (!s)
		return ;
	f = (*s && ft_strlen(*s) > 1);
	i = -1;
	while (s[++i])
	{
		j = -1;
		while (s[i][++j])
			if (s[i][j] == -2 && !f)
				s[i][j] = '\0';
		if (f)
			replace_character(s[i], -2);
	}
}
