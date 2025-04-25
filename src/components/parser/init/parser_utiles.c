/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:23:27 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/25 15:51:07 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

void	set_empty_one(char *val)
{
	if (!val)
		return ;
	while (*val)
	{
		if (*val == -2)
			*val = '\0';
		val++;
	}
}

t_cmd	*new_cmd_val(char *val, t_TokenType typ)
{
	t_cmd	*new;

	new = ft_malloc(sizeof(t_cmd));
	new->cmd = NULL;
	new->pip_infront = false;
	new->pip_infront = 0;
	new->next = NULL;
	if (typ == COMMAND)
	{
		new->cmd = ft_split_adv(val);
		set_empty_str(new->cmd);
		set_zero_space(new->cmd);
	}
	set_back_space(val);
	set_empty_one(val);
	new->fd_herdoc = 0;
	new->type = typ;
	new->value = val;
	return (new);
}

char	*join_args(char **sp)
{
	int		i;
	char	*tmp;

	if (!sp)
		return (NULL);
	i = 1;
	tmp = NULL;
	while (sp[i])
	{
		sp[i] = ft_strjoin(sp[i], " ");
		tmp = ft_strjoin(tmp, sp[i]);
		i++;
	}
	return (tmp);
}

char	*join_arg_two(char **sp)
{
	int		i;
	char	*tmp;

	if (!sp)
		return (NULL);
	i = 0;
	tmp = NULL;
	while (sp[i])
	{
		sp[i] = ft_strjoin(sp[i], " ");
		tmp = ft_strjoin(tmp, sp[i]);
		i++;
	}
	return (tmp);
}

char	**join_args_adv(char **s1, char **s2)
{
	char	**ret;
	char	*tmp;

	tmp = ft_strjoin(join_arg_two(s1), join_args(s2));
	ret = ft_split_adv(tmp);
	if (!ret)
		return (NULL);
	set_zero_space(ret);
	set_empty_str(ret);
	return (ret);
}
