/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoats_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 02:19:20 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/10 10:27:40 by iezzam           ###   ########.fr       */
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

char	*mixed_qoats(char *s)
{
	char	**double_q;
	char	*final;
	int		i;
	
	i = 0;
	final = NULL;
	double_q = ft_split(s, '\"');
	while (double_q[i])
	{
		final = ft_strjoin(final, double_q[i]);
		i++;
	}
	return (final);
}


// voidqoated_str_handler(char *);
void	command_handler(t_node *node)
{
	if (there_is_qoats(node->value))
	
	if (singlq_only(node->value))
		node->value = ft_remove_char(node->value, '\'');
	else if (doubleq_only(node->value))
		node->value = ft_remove_char(node->value, '"');
	else
		node->value = mixed_qoats(node->value);
}
