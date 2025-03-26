/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:41:43 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/26 20:42:00 by iezzam           ###   ########.fr       */
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
