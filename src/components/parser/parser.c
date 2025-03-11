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
		new->cmd = ft_split(val, ' ');
	new->type = typ;
	new->value = val;
	return (new);
}

void	handel_outfile(t_cmd **head, char *val, int f)
{
	char	**sp;
	int		i;

	sp = ft_split(val, ' ');
	if (!sp[1])
		return (add_to_cmd(head, new_cmd_val(val, OUT_FILE)));
	i = 0;
	add_to_cmd(head, new_cmd_val(sp[i], OUT_FILE));
	while (sp[++i])
	{
		if (f == 0)
			add_to_cmd(head, new_cmd_val(sp[i], COMMAND));
		else
			add_to_cmd(head, new_cmd_val(sp[i], SIMPLE_FILE));
	}
}

void	handel_infile(t_cmd **head, char *val, int f)
{
	char	**sp;
	int		i;
	int		k;

	sp = ft_split(val, ' ');
	if (!sp[1])
		return (add_to_cmd(head, new_cmd_val(val, IN_FILE)));
	i = 0;
	k = 0;
	add_to_cmd(head, new_cmd_val(sp[i], IN_FILE));
	while (sp[++i])
	{
		if (f == 0)
		{
			if (k == 0)
				add_to_cmd(head, new_cmd_val(sp[i], COMMAND));
			else
				add_to_cmd(head, new_cmd_val(sp[i], SIMPLE_FILE));
			k++;
		}
		else
			add_to_cmd(head, new_cmd_val(sp[i], SIMPLE_FILE));
	}
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
		{
			handel_outfile(&new, head->next->value, i);
			head = head->next;
		}
		else if (head->next && head->type == APPEND)
		{
			add_to_cmd(&new, new_cmd_val(head->next->value, APPEND));
			head = head->next;
		}
		else if (head->next && head->type == LEFT_RED)
		{
			handel_infile(&new, head->next->value, i);
			head = head->next;
		}
		i++;
		head = head->next;
	}
	return (new);
}

int parser(t_data *data)
{
	t_node *tock_data;

	tock_data = lexer_init(data->prompt);
	free(data->prompt);
	data->prompt = NULL;
	if (!tock_data)
		return (0);
	if (syntax_checker(tock_data) == -1)
		return (0);
	else
		data->head = data_maker(tock_data, data->final_env);
	if (!data->head)
		return (0);
	data->head = final_data(data->head);
	return (1);
}
