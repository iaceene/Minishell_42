/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:28:39 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/22 10:08:41 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

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

	(1) && (i = 0, word = NULL, ex_flag = false, count = ft_count_str(splited));
	if (splited[0] && ft_strncmp(splited[0], "export", \
		ft_strlen("export")) == 0)
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
		(1) && (word = ft_strjoin(word, splited[i]), i++);
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
