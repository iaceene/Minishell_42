/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_file_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:22:19 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/25 21:33:28 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int handle_input_redirection(t_cmd *cmd, int *infile)
{
	if (*infile != -1)
	{
		close(*infile);
		*infile = -1;
	}

	*infile = open(cmd->value, O_RDONLY);
	if (*infile == -1)
	{
		perror(cmd->value);
		return (-1);
	}
	return (0);
}

int handle_output_redirection(t_cmd *cmd, int *outfile)
{
	if (*outfile != -1)
	{
		close(*outfile);
		*outfile = -1;
	}

	*outfile = open(cmd->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*outfile == -1)
	{
		perror(cmd->value);
		return (-1);
	}
	return (0);
}

int handle_append_redirection(t_cmd *cmd, int *outfile)
{
	if (*outfile != -1)
	{
		close(*outfile);
		*outfile = -1;
	}

	*outfile = open(cmd->value, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (*outfile == -1)
	{
		perror(cmd->value);
		return (-1);
	}
	return (0);
}

int handle_file_redirection(t_cmd *cmd, int *infile, int *outfile,
							t_pipex_data *data)
{
	(void)data;
	t_cmd *current;

	current = cmd;
	current = cmd->next;
	while (current)
	{
		if (current->type == COMMAND)
			break;
		if (current->type == IN_FILE)
		{
			if (handle_input_redirection(current, infile) == -1)
				return (-1);
		}
		else if (current->type == OUT_FILE)
		{
			if (handle_output_redirection(current, outfile) == -1)
				return (-1);
		}
		else if (current->type == APPEND)
		{
			if (handle_append_redirection(current, outfile) == -1)
				return (-1);
		}
		else if (current->type == HERDOC)
		{
			if (dup2(current->fd_herdoc, STDIN_FILENO) == -1)
				perror("dup2 rediretcion");
			close(current->fd_herdoc);
		}
		current = current->next;
	}
	return (0);
}