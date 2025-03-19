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

#include "../../../../include/parser.h"

void	handle_outfile(t_cmd **head, char *val)
{
	char	**sp;
	t_cmd	*lst_cmd;

	sp = ft_split(val, ' ');
	if (!sp)
		return (add_to_cmd(head, new_cmd_val(ft_strdup(""), OUT_FILE)));
	if (!sp[1])
		return (add_to_cmd(head, new_cmd_val(val, OUT_FILE)));
	else
	{
		add_to_cmd(head, new_cmd_val(sp[0], OUT_FILE));
		if (!get_last_cmd_pip(*head))
			add_to_cmd(head, new_cmd_val(join_args(sp), COMMAND));
		else if (get_last_cmd_pip(*head))
		{
			lst_cmd = get_last_cmd_pip(*head);
			if (!lst_cmd)
				return ;
			lst_cmd->cmd = join_args_adv(lst_cmd->cmd, sp);
		}
	}
}

void	handle_append(t_cmd **head, char *val)
{
	char	**sp;
	t_cmd	*lst_cmd;

	sp = ft_split(val, ' ');
	if (!sp)
		return (add_to_cmd(head, new_cmd_val(ft_strdup(""), APPEND)));
	if (!sp[1])
		return (add_to_cmd(head, new_cmd_val(val, APPEND)));
	else
	{
		add_to_cmd(head, new_cmd_val(sp[0], APPEND));
		if (!get_last_cmd_pip(*head))
			add_to_cmd(head, new_cmd_val(join_args(sp), COMMAND));
		else if (get_last_cmd_pip(*head))
		{
			lst_cmd = get_last_cmd_pip(*head);
			if (!lst_cmd)
				return ;
			lst_cmd->cmd = join_args_adv(lst_cmd->cmd, sp);
		}
	}
}

void	handle_infile(t_cmd **head, char *val)
{
	char	**sp;
	t_cmd	*lst_cmd;

	sp = ft_split(val, ' ');
	if (!sp)
		return (add_to_cmd(head, new_cmd_val(ft_strdup(""), IN_FILE)));
	if (!sp[1])
		return (add_to_cmd(head, new_cmd_val(val, IN_FILE)));
	else
	{
		add_to_cmd(head, new_cmd_val(sp[0], IN_FILE));
		if (!get_last_cmd_pip(*head))
			add_to_cmd(head, new_cmd_val(join_args(sp), COMMAND));
		else if (get_last_cmd_pip(*head))
		{
			lst_cmd = get_last_cmd_pip(*head);
			if (!lst_cmd)
				return ;
			lst_cmd->cmd = join_args_adv(lst_cmd->cmd, sp);
		}
	}
}

t_cmd	*new_herdoc(char *val, t_env *env, t_cmd **head)
{
	t_cmd	*new;

	new = ft_malloc(sizeof(t_cmd));
	new->next = NULL;
	new->type = HERDOC;
	new->value = val;
	new->fd_herdoc = herdoc(env, get_last_cmd(*head), head, val);
	return (new);
}

void	add_pip_flag(t_cmd *head)
{
	t_cmd	*last_cmd;

	if (!head)
		return ;
	last_cmd = get_last_cmd(head);
	if (!last_cmd)
		return ;
	last_cmd->pip_infront = true;
}

t_cmd	*final_data(t_cmd *head, t_env *env)
{
	t_cmd	*new;

	new = NULL;
	while (head)
	{
		if (head->type == COMMAND)
			add_to_cmd(&new, new_cmd_val(head->value, COMMAND));
		else if (head->type == PIPE)
			add_pip_flag(new);
		else if (head->next && head->type == RIGHT_RED)
			handle_outfile(&new, head->next->value);
		else if (head->next && head->type == APPEND)
			handle_append(&new, head->next->value);
		else if (head->next && head->type == LEFT_RED)
			handle_infile(&new, head->next->value);
		else if (head->type == HERDOC)
			add_to_cmd(&new, new_herdoc(head->value, env, &new));
		if (head->next && (head->type == RIGHT_RED || head->type == APPEND || \
			head->type == LEFT_RED))
			head = head->next;
		head = head->next;
	}
	return (new);
}

int	heredoc_quit(t_cmd	*head)
{
	while (head)
	{
		if (head->type == HERDOC && head->fd_herdoc == -99)
			return (1);
		head = head->next;
	}
	return (0);
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
	data->head = final_data(data->head, data->final_env);
	if (heredoc_quit(data->head))
		return (-99);
	// reforme_data(&data->head);
	return (1);
}
