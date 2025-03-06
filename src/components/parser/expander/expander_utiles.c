/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 23:58:48 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/06 21:56:05 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

int	is_sperator(char c)
{
	return (c == '-' || c == ' ' || c == '\t' || c == '\'' || c == '"' || c == '$');
}

char	*ft_strndup(char *s, size_t n)
{
	char	*ret;
	size_t	i;

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
	if (!str[i + 1])
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

char	*get_val(char *str)
{
	char	*name;
	char	*ret;

	name = extract_name(str);
	if (!name)
		return (ft_strdup(""));
	ret = getenv(name);
	return (ret);
}

char	*join_all(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(s1, s2);
	ret = ft_strjoin(tmp, s3);
	return (ret);
}

char	*expand_this(char *str)
{
	char	*before;
	char	*after;
	char	*expand;

	while (1)
	{
		if (!find_it(str, '$'))
			break ;
		before = get_before(str);
		after = get_after(str);
		expand = get_val(str);
		if (!expand)
			expand = ft_strdup("");
		str = join_all(before, expand, after);
		// printf("here\n");
	}
	return (str);
}
