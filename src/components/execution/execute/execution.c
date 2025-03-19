/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:23:52 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/26 16:51:29 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

int	ft_lstsize_head(t_cmd *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

static void	handle_single_command(t_cmd *exec_list, t_env **env, \
			int *exit_status, t_pipex_data *data)
{
	t_cmd	*cmd;

	cmd = exec_list;
	handle_file_redirection(cmd, &data->infile, &data->outfile);
	while (cmd && cmd->type != COMMAND)
		cmd = cmd->next;
	if (cmd)
		execution_cmd(cmd->cmd, env, exit_status);
}

void	execution(t_cmd **head, t_env **env, int *exit_status)
{
	int				cmd_count;
	t_pipex_data	data;
	t_cmd			*tmp;

	if (!head || !*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		if (tmp->type != COMMAND)
			tmp->cmd = NULL;
		tmp = tmp->next;
	}
	cmd_count = ft_lstsize_head(*head);
	if (cmd_count == 0)
		return ;
	if (cmd_count == 1)
		handle_single_command(*head, env, exit_status, &data);
	else
		ft_pipex(*head, env, exit_status);
}
