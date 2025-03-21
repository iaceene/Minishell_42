/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:43:44 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/21 00:39:33 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

char	*remove_qoats(char *s)
{
	char	*result;
	int		i;
	int		j;
	bool	in_single_quotes;
	bool	in_double_quotes;

	if (!s)
		return (NULL);
	result = ft_malloc(strlen(s) + 1);
	i = 0;
	j = 0;
	in_single_quotes = false;
	in_double_quotes = false;
	while (s[i])
	{
		if (s[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (s[i] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else
			result[j++] = s[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

t_cmd	*new_cmd_hered(char **val)
{
	t_cmd	*ret;

	ret = ft_malloc(sizeof(t_cmd));
	ret->cmd = val;
	ret->type = COMMAND;
	ret->next = NULL;
	ret->value = NULL;
	return (ret);
}

int	herdoc(t_env *env, t_cmd *commnd, t_cmd **head, char *exit)
{
	int		fd;
	bool	qoated;
	char	**arg;

	fd = -1;
	qoated = will_expanded(exit);
	set_space_zero_qoats(exit);
	arg = ft_split(exit, ' ');
	if (!arg)
		return (-1);
	set_zero_space(arg);
	exit = remove_qoats(arg[0]);
	if (commnd)
		commnd->cmd = join_args_adv(commnd->cmd, arg);
	else if (arg && *(arg + 1))
		add_to_cmd(head, new_cmd_hered(arg + 1));
	fd = get_herdoc_fd(env, exit, qoated, env->data->exe_state);
	return (fd);
}
