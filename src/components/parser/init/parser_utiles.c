/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:23:27 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/24 01:00:55 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

void	set_empty_one(char *val)
{
	while (*val)
	{
		if (*val == -2)
			*val = '\0';
		val++;
	}
}
	
t_cmd	*new_cmd_val(char *val, TokenType typ)
{
	t_cmd	*new;

	new = ft_malloc(sizeof(t_cmd));
	new->cmd = NULL;
	new->files = NULL;
	new->next = NULL;
	if (typ == COMMAND)
	{
		new->cmd = ft_split(val, ' ');
		set_empty_str(new->cmd);
		set_zero_space(new->cmd);
	}
	set_empty_one(val);
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
	ret = ft_split(tmp, ' ');
	if (!ret)
		return (NULL);
	set_zero_space(ret);
	set_empty_str(ret);
	return (ret);
}

t_cmd	*get_last_cmd(t_cmd *head)
{
	t_cmd	*last;

	if (!head)
		return (NULL);
	if (head->type == COMMAND)
		last = head;
	else
		last = NULL;
	while (head)
	{
		if (head->type == COMMAND)
			last = head;
		head = head->next;
	}
	return (last);
}
