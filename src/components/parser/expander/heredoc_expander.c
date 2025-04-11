/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:28:39 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/11 19:59:17 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

char	*extract_name_hr(char	*str)
{
	int		len;
	char	*ret;

	len = 0;
	while (str[len] && !is_sperator(str[len]))
		len++;
	if (!len)
		return (NULL);
	ret = ft_malloc(len + 1);
	len = 0;
	while (str[len] && !is_sperator(str[len]))
	{
		ret[len] = str[len];
		len++;
	}
	ret[len] = '\0';
	return (ret);
}

char	*extract_left_hr(char	*str)
{
	int		len;
	int		actual_len;
	char	*ret;

	if (!str)
		return (NULL);
	len = 0;
	actual_len = ft_strlen(str);
	while (str[len] && !is_sperator(str[len]))
		len++;
	ret = ft_malloc(actual_len - len + 1);
	actual_len = 0;
	while (str[len])
	{
		ret[actual_len] = str[len];
		len++;
		actual_len++;
	}
	ret[len] = '\0';
	return (ret);
}

char	*exe_expand(char *str, t_env *env, int exit)
{
	char	*word;
	char	*left;

	(void)exit;
	left = extract_left_hr(str);
	word = extract_name_hr(str);
	while (env)
	{
		if (ft_strcmp(env->key, word) == 0)
		{
			word = env->value;
			break ;
		}
		env = env->next;
	}
	if (!env)
		return (ft_strjoin(NULL, left));
	return (ft_strjoin(word, left));
}

char	*expand_this_str(char *str, t_env *env, int exit)
{
	char	*word;
	int		i;
	char	**splited;

	i = 0;
	word = NULL;
	splited = ft_split(str, '$');
	while (splited[i])
	{
		splited[i] = exe_expand(splited[i], env, exit);
		i++;
	}
	i = 0;
	while (splited[i])
	{
		word = ft_strjoin(word, splited[i]);
		i++;
	}
	return (word);
}

char	*heredoc_expander(char *str, t_env	*env, int exit)
{
	if (!str || !env)
		return (NULL);
	if (!find_it(str, '$'))
		return (str);
	return (expand_this_str(str, env, exit));
}
