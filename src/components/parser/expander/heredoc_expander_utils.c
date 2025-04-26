/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:28:39 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/26 17:42:53 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

static char	*extract_name_hr(char	*str, int *re_len)
{
	int		len;
	char	*ret;

	len = 0;
	while (str[len] && !is_sperator(str[len]))
	{
		len++;
		if (ft_isdigit(str[len]) && ft_isdigit(str[0]))
			break ;
	}
	if (!len)
		return (NULL);
	ret = ft_malloc(len + 1);
	*re_len = len;
	ret[len] = '\0';
	return (ft_strncpy(ret, str, len));
}

static char	*extract_left_hr(char *str, int start)
{
	int		len;
	char	*ret;

	if (!str || !*(str + start))
		return (ft_strdup(""));
	len = ft_strlen(str + start);
	if (len == 0)
		return (ft_strdup(""));
	ret = ft_malloc(len + 1);
	return (ft_strcpy(ret, str + start));
}

char	*exe_expand(char *str, t_env *env, int exit, bool flag)
{
	char	*word;
	char	*left;
	int		start;

	if (flag)
		return (str);
	word = extract_name_hr(str, &start);
	left = extract_left_hr(str, start);
	while (env)
	{
		if (ft_strcmp(env->key, word) == 0)
		{
			word = env->value;
			break ;
		}
		env = env->next;
	}
	if (ft_strcmp("?", word) == 0)
		return (ft_strjoin(ft_itoa(exit), left));
	if (!env)
		return (ft_strjoin(ft_strdup(""), left));
	return (ft_strjoin(word, left));
}
