/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:28:39 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/21 21:14:08 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

char	*extract_name_hr(char	*str, int *re_len)
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
	return (ft_strncpy(ret, str, len));
}

char	*extract_left_hr(char *str, int	start)
{
	int		len;
	char	*ret;

	if (!str || !(str + start))
		return (NULL);
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

int	ft_count_str(char **str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_set_export(char *word)
{
	if (!word || !find_it(word, '='))
		return ;
	while (*word && !ft_isspace(*word))
		word++;
	if (*word)
		word++;
	else
		return ;
	set_space_excep(word);
}

char	*apply_expand(char **splited, int exit, t_env *env, bool flag)
{
	bool	ex_flag;
	int		i;
	char	*word;
	int		count;

	i = 0;
	word = NULL;
	ex_flag = false;
	count = ft_count_str(splited);
	if (splited[0] && ft_strncmp(splited[0], "export", ft_strlen("export")) == 0)
		ex_flag = true;
	while (splited[i])
	{
		splited[i] = exe_expand(splited[i], env, exit, flag);
		flag = false;
		i++;
	}
	i = 0;
	while (i < count)
	{
		if (!splited[i])
			splited[i] = ft_strdup("");
		word = ft_strjoin(word, splited[i]);
		i++;
	}
	if (ex_flag)
		ft_set_export(word);
	return (word);
}

char	*expand_this_str(char *str, t_env *env, int exit)
{
	bool	flag;
	int		i;
	char	**splited;

	i = 0;
	flag = true;
	if (!str)
		return (ft_strdup(""));
	hard_code_pid(str);
	if (str[0] == '$')
		flag = false;
	splited = ft_split(str, '$');
	return (apply_expand(splited, exit, env, flag));
}

char	*heredoc_expander(char *str, t_env	*env, int exit)
{
	char	*exp;

	if (!str || !env)
		return (NULL);
	if (!find_it(str, '$'))
		return (str);
	exp = expand_this_str(str, env, exit);
	return (set_dollars(exp));
}
