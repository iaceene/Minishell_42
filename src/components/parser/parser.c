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

void	handle_outfile(t_cmd **head, char *val)
{
	char	**sp;

	sp = ft_split(val, ' ');
	if (!sp)
		return (add_to_cmd(head, new_cmd_val(ft_strdup(""), OUT_FILE)));
	if (!sp[1])
		return (add_to_cmd(head, new_cmd_val(val, OUT_FILE)));
	add_to_cmd(head, new_cmd_val(sp[0], OUT_FILE));
	add_to_cmd(head, new_cmd_val(join_args(sp), COMMAND));
}

void	handle_infile(t_cmd **head, char *val)
{
	char	**sp;

	sp = ft_split(val, ' ');
	if (!sp)
		return (add_to_cmd(head, new_cmd_val(ft_strdup(""), IN_FILE)));
	if (!sp[1])
		return (add_to_cmd(head, new_cmd_val(val, IN_FILE)));
	add_to_cmd(head, new_cmd_val(sp[0], IN_FILE));
	add_to_cmd(head, new_cmd_val(join_args(sp), COMMAND));
}

t_cmd	*final_data(t_cmd *head)
{
	t_cmd	*new;
	int		i;

	new = NULL;
	i = 0;
	while (head)
	{
		if (head->type == COMMAND)
			add_to_cmd(&new, new_cmd_val(head->value, COMMAND));
		else if (head->next && head->type == RIGHT_RED)
			handle_outfile(&new, head->next->value);
		else if (head->next && head->type == APPEND)
			add_to_cmd(&new, new_cmd_val(head->next->value, APPEND));
		else if (head->next && head->type == LEFT_RED)
			handle_infile(&new, head->next->value);
		if (head->next && (head->type == RIGHT_RED || head->type == APPEND
				|| head->type == LEFT_RED))
			head = head->next;
		i++;
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
	data->head = data_maker(tock_data, data->final_env);
	if (!data->head)
		return (0);
	data->head = final_data(data->head);
	return (1);
}
