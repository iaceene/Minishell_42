/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 23:58:48 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/26 03:15:03 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

char	*ft_getenv(char *name, t_env *env)
{
	if (!name || !env)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(name, env->key, ft_strlen(name) + 1) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*get_val(char *str, t_env *env, int exit_status)
{
	char	*name;
	char	*ret;

	name = extract_name(str);
	if (name && ft_strncmp(name, "?", 1) == 0)
		return (ft_itoa(exit_status));
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
	if (!tmp)
		return (NULL);
	ret = ft_strjoin(tmp, s3);
	return (ret);
}

static int	count_dollars(char *s)
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

char	*expand_this(char *str, t_env *env, int exit_status)
{
	int		count;
	char	*before;
	char	*after;
	char	*expand;
	char	*new_str;

	count = count_dollars(str);
	while (count-- > 0)
	{
		before = get_before(str);
		after = get_after(str);
		expand = get_val(str, env, exit_status);
		new_str = join_all(before, expand, after);
		str = new_str;
		if (!str)
			return (NULL);
	}
	return (str);
}
