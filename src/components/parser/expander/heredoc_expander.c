/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:28:39 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/25 15:38:17 by yaajagro         ###   ########.fr       */
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

char	*apply_expand(char **splited, int exit, t_env *env, bool flag)
{
	int		i;
	char	*word;
	int		count;

	i = 0;
	word = NULL;
	count = ft_count_str(splited);
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
	return (word);
}

char	*expand_this_str(char *str, t_env *env, int exit)
{
	bool	flag;
	char	**splited;

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
