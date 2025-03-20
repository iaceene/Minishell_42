/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 22:07:36 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/31 18:36:37 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execution.h"

t_cmd	*new_cmd_val(char *val, TokenType typ)
{
	t_cmd	*new;

	new = ft_malloc(sizeof(t_cmd));
	new->next = NULL;
	if (typ == COMMAND)
	{
		new->cmd = ft_split(val, ' ');
		set_empty_str(new->cmd);
		set_zero_space(new->cmd);
	}
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
	set_zero_space(ret);
	set_empty_str(ret);
	return (ret);
}

t_cmd	*get_last_cmd(t_cmd *head)
{
	t_cmd	*prv;

	prv = head;
	while (head && head->next)
	{
		prv = head;
		head = head->next;
	}
	return (prv);
}

void	handle_outfile(t_cmd **head, char *val, t_cmd *prv)
{
	char	**sp;
	t_cmd	*lst_cmd;

	sp = ft_split(val, ' ');
	if (!sp)
		return (add_to_cmd(head, new_cmd_val(ft_strdup(""), OUT_FILE)));
	if (!sp[1])
		return (add_to_cmd(head, new_cmd_val(val, OUT_FILE)));
	add_to_cmd(head, new_cmd_val(sp[0], OUT_FILE));
	if (!prv || prv->type != COMMAND)
		add_to_cmd(head, new_cmd_val(join_args(sp), COMMAND));
	else
	{
		lst_cmd = get_last_cmd(*head);
		lst_cmd->cmd = join_args_adv(lst_cmd->cmd, sp);
	}
}

void	handle_infile(t_cmd **head, char *val, t_cmd *prv)
{
	char	**sp;
	t_cmd	*lst_cmd;

	sp = ft_split(val, ' ');
	if (!sp)
		return (add_to_cmd(head, new_cmd_val(ft_strdup(""), IN_FILE)));
	if (!sp[1])
		return (add_to_cmd(head, new_cmd_val(val, IN_FILE)));
	add_to_cmd(head, new_cmd_val(sp[0], IN_FILE));
	if (!prv || prv->type != COMMAND)
		add_to_cmd(head, new_cmd_val(join_args(sp), COMMAND));
	else
	{
		lst_cmd = get_last_cmd(*head);
		lst_cmd->cmd = join_args_adv(lst_cmd->cmd, sp);
	}
}

t_cmd	*new_herdoc(char *val, t_env *env, t_cmd **head, int ex)
{
	t_cmd	*new;

	new = ft_malloc(sizeof(t_cmd));
	new->next = NULL;
	new->type = HERDOC;
	new->value = val;
	new->fd_herdoc = herdoc(env, get_last_cmd(*head), head, val, ex);
	return (new);
}

t_cmd	*final_data(t_cmd *head, t_env *env, int ex)
{
	t_cmd	*new;
	t_cmd	*prv;

	new = NULL;
	prv = NULL;
	while (head)
	{
		if (head->type == COMMAND)
			add_to_cmd(&new, new_cmd_val(head->value, COMMAND));
		else if (head->next && head->type == RIGHT_RED)
			handle_outfile(&new, head->next->value, prv);
		else if (head->next && head->type == APPEND)
			add_to_cmd(&new, new_cmd_val(head->next->value, APPEND));
		else if (head->next && head->type == LEFT_RED)
			handle_infile(&new, head->next->value, prv);
		else if (head->type == HERDOC)
			add_to_cmd(&new, new_herdoc(head->value, env, &new, ex));
		if (head->next && (head->type == RIGHT_RED || head->type == APPEND
				|| head->type == LEFT_RED))
			head = head->next;
		prv = head;
		head = head->next;
	}
	return (new);
}

int	parser(t_data *data)
{
	t_node	*tock_data;

	tock_data = lexer_init(data->prompt);
	free(data->prompt);
	data->prompt = NULL;
	if (!tock_data)
		return (0);
	if (syntax_checker(tock_data) == -1)
		return (0);
	data->head = data_maker(tock_data, data->final_env, data->exe_state);
	if (!data->head)
		return (0);
	data->head = final_data(data->head, data->final_env, data->exe_state);
	return (1);
}
