/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 23:58:48 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/12 21:08:39 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

char	*ft_getenv(char *name, t_env *env)
{
	if (!name || !env)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(name, env->key, ft_strlen(name)) == 0
			&& ft_strlen(name) == ft_strlen(env->key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*get_val(char *str, t_env *env)
{
	char	*name;
	char	*ret;

	name = extract_name(str);
	if (ft_strncmp(name, "?", ft_strlen(name)) == 0
		&& ft_strlen(name) == ft_strlen("?"))
		return (ft_strdup("$?"));
	if (!name)
		return (ft_strdup("$"));
	ret = ft_getenv(name, env);
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

char	*expand_this(char *str, t_env *env)
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
		expand = get_val(str, env);
		if (!expand)
			expand = ft_strdup("");
		str = join_all(before, expand, after);
	}
	return (str);
}
