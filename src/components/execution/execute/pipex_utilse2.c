/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utilse1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:24:36 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/18 06:24:36 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

void	ft_check(t_cmd **head)
{
	perror((*head)->value);
	*head = (*head)->next;
}

void	ft_sort(t_cmd **head)
{
	t_cmd	*tmp;
	t_cmd	*last;
	t_cmd	*first_cmd;

	(1) && (last = NULL, first_cmd = NULL);
	if (!head || !*head || (*head)->type == COMMAND)
		return ;
	if ((*head)->type == IN_FILE && access((*head)->value, F_OK)
		&& (*head)->next)
		return (ft_check(head));
	tmp = *head;
	while (tmp && tmp->type != COMMAND)
	{
		last = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	first_cmd = tmp;
	if (last)
	{
		last->next = first_cmd->next;
		first_cmd->next = *head;
		*head = first_cmd;
	}
}

bool	get_prv_cmd(t_cmd *head, int count)
{
	int	i;

	i = 0;
	while (head && i <= count)
	{
		return (head->pip_infront);
		head = head->next;
		i++;
	}
	return (0);
}

int	silence_output_if_needed(t_pipex_data *data)
{
	int	null_fd;

	null_fd = -1;
	if (get_prv_cmd(data->head, data->current_cmd))
	{
		null_fd = open("/dev/null", O_WRONLY);
		if (null_fd == -1)
		{
			perror("open /dev/null");
			return (-1);
		}
		if (dup2(null_fd, STDOUT_FILENO) == -1 || \
			dup2(null_fd, STDERR_FILENO) == -1)
		{
			perror("dup2 (silencing output)");
			close(null_fd);
			return (-1);
		}
		close(null_fd);
		return (-1);
	}
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		perror("dup2 outfile");
	close(data->outfile);
	return (0);
}
