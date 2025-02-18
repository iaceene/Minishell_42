/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoats_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 02:19:20 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/11 05:00:27 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parser.h"

int there_is_qoats(char *s)
{
	while (*s)
	{
		if (*s == '\'')
			return (1);
		if (*s == '"')
			return (2);
		s++;
	}
	return (0);
}

int singlq_only(char *s)
{
	while (*s)
	{
		if (*s == '"')
			return (0);
		s++;
	}
	return (1);
}

int doubleq_only(char *s)
{
	while (*s)
	{
		if (*s == '\'')
			return (0);
		s++;
	}
	return (1);
}

char *ft_remove_char(char *s, char c)
{
	char	*ret;
	int		len;
	int		i;

	ret = s;
	len = 0;
	i = 0;
	while (*ret)
	{
		if (*ret != c)
			len++;
		ret++;
	}
	ret = ft_malloc(len + 1);
	len = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			ret[len] = s[i];
			len++;
		}
		i++;
	}
	ret[len] = '\0';
	return (ret);
}

int no_qoats(char *s)
{
	while (*s)
	{
		if (*s == '\'')
			return (0);
		s++;
	}
	return (1);
}

char	*mixed_qoats(char *s, t_fake_env *env)
{
	char	**double_q;
	char	*final;
	int		i;
	
	i = 0;
	final = NULL;
	(void)env;
	double_q = ft_split(s, '\"');
	while (double_q[i])
	{
		printf("-> %s\n", double_q[i]);
		final = ft_strjoin(final, double_q[i]);
		i++;
	}
	final = ft_remove_char(final, '\'');
	return (final);
}

int	ft_find(char *s, char c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

char *qoated_str_handler(char *str, t_fake_env *env)
{
	char	*tmp;

	if (singlq_only(str))
		return (ft_remove_char(str, '\''));
	else if (doubleq_only(str))
	{
		tmp = ft_remove_char(str, '"');
		if (ft_find(tmp, '$'))
			return (expander(tmp, env));
		else
			return (tmp);
	}
	else
		return (mixed_qoats(str, env));
}

void command_handler(t_node *node, t_fake_env *env)
{
	if (there_is_qoats(node->value))
		node->value = qoated_str_handler(node->value, env);
	// if (ft_find(node->value, '$'))
	// 	node->value = expander(node->value, env);
}
