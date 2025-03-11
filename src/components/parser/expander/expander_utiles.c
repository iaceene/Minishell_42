/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 23:58:48 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/11 23:27:29 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

char	*get_val(char *str)
{
	char	*name;
	char	*ret;

	name = extract_name(str);
	if (!name)
		return (ft_strdup("$"));
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

int	count_dollars(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == '$')
			count++;
		s++;
	}
	return (count);
}

char	*expand_this(char *str)
{
	int		count;
	char	*before;
	char	*after;
	char	*expand;

	count = count_dollars(str);
	while (--count >= 0)
	{
		before = get_before(str);
		after = get_after(str);
		expand = get_val(str);
		if (!expand)
			expand = ft_strdup("");
		str = join_all(before, expand, after);
	}
	return (str);
}
