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

#include "../../../../include/minishell.h"

int ft_lstsize_head(t_exec *lst)
{
	int i;

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

t_exec *copy_cmd_to_exec(t_cmd *cmd)
{
	t_exec *new_exec;
	t_exec *current_exec;
	t_exec *new_node;

	new_exec = NULL;
	current_exec = NULL;
	while (cmd)
	{
		new_node = ft_malloc(sizeof(t_exec));
		if (!new_node)
			return (NULL);
		new_node->type = cmd->type;
		new_node->value = ft_strdup(cmd->value);
		new_node->s = cmd->cmd;
		if (!new_node->value)
			return (NULL);
		new_node->next = NULL;
		if (new_exec == NULL)
			new_exec = new_node;
		else
			current_exec->next = new_node;
		current_exec = new_node;
		cmd = cmd->next;
	}
	return (new_exec);
}

static void handle_single_command(t_exec *exec_list, t_env **env,
								  int *exit_status, t_pipex_data *data)
{
	t_exec *cmd;

	cmd = exec_list;

	handle_file_redirection(cmd, &data->infile, &data->outfile, data);


	while (cmd && cmd->type != COMMAND)
		cmd = cmd->next;
	if (cmd)
	{
		execution_cmd(cmd->s, env, exit_status);
	}
}

void execution(t_cmd **head, t_env **env, int *exit_status)
{
	int cmd_count;
	t_exec *exec_list;
	t_pipex_data data;

	if (!head || !*head)
		return;
	exec_list = copy_cmd_to_exec(*head);
	if (!exec_list)
	{
		perror("Error: Failed to copy command list");
		return;
	}
	cmd_count = ft_lstsize_head(exec_list);
	if (cmd_count == 0)
		return;
	if (cmd_count == 1)
		handle_single_command(exec_list, env, exit_status, &data);
	else
		ft_pipex(exec_list, env, exit_status);
}
