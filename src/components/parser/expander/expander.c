/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 02:14:23 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/11 04:32:53 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

char *find_dollar(char *s)
{
	int flag;
	int count;

	flag = 0;
	count = 0;
	while (*s)
	{
		if (*s == '\'')
		{
			flag = 1;
			count++;
			if (count %  2 == 0)
				flag = 0;
		}
		if (*s == '$' && flag == 0)
			return (s + 1);
		s++;
	}
	return (s);
}

char *copy_until_space(char *s)
{
    char *tmp;
    int len;

    if (!s)
		return (NULL);
	len = 0;
	s = find_dollar(s);
	tmp = s;
	while (*s && !ft_isspace(*s))
	{
		len++;
		s++;
	}
	tmp = ft_strndup(tmp, len);
    return (tmp);
}

char *copy_befor_dlr(char *s)
{
    char *tmp;
    int len;

    if (!s) return NULL;

    len = 0;
    while (s[len] && s[len] != '$')
        len++;

    tmp = ft_malloc(len + 1);
    if (!tmp) return NULL;

    for (int i = 0; i < len; i++)
        tmp[i] = s[i];
    tmp[len] = '\0';

    return tmp;
}

char *copy_after_dlr(char *s)
{
    char *dollar_pos = find_dollar(s);
	while (*dollar_pos && !ft_isspace(*dollar_pos))
		dollar_pos++;
    if (!dollar_pos || !*dollar_pos)
		return (NULL);
    return ft_strdup(dollar_pos);
}

char *expand_one_arg(char *s, t_fake_env *head)
{
	char	*befor_dolar;
	char	*after_dolar;

	if (!*s || !s)
		return (NULL);
	befor_dolar = copy_befor_dlr(s);
	after_dolar = copy_after_dlr(s);
	s = copy_until_space(s);
	while (head)
	{
		if (!s || !*s)	
			return (ft_strjoin(befor_dolar, after_dolar));
		if (ft_strncmp(s, head->key, ft_strlen(head->key)) == 0
			&& ft_strlen(s) == ft_strlen(head->key))
			break ;
		head = head->next;
	}
	if (!head)
		return (ft_strjoin(befor_dolar, after_dolar));
	else
	{
		s = ft_strjoin(befor_dolar, head->value);
		return (ft_strjoin(s, after_dolar));
	}
	return (NULL);
}

char *expander_init(char *s, t_fake_env *head)
{
	int		count;
	char	*position;

	count = 0;
	position = s;
	while (*position)
	{
		if (*position == '$')
			count++;
		position++;
	}
	if (count == 1)
		return (expand_one_arg(s, head));
	else if (count > 1)
		return(multiple_var_expander(s, head));
	return (NULL);
}

char	*no_provided_var(char *s)
{
	char	*tmp;
	int		len;

	len = 0;
	tmp = s;
	while (*tmp && *tmp != '$')
	{
		tmp++;
		len++;
	}
	return (ft_strndup(s, len - 1));
}

char	*expander(char *node, t_fake_env *head)
{
	char    *position;
	char	*expanded;

	position = find_dollar(node);
	if(!position || !*position)
		return (no_provided_var(node));
	expanded = expander_init(node, head);
	if (!expanded)
		return (NULL);
	return (expanded);
}
