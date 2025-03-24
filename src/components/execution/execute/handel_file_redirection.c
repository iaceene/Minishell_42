/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_file_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:22:19 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/24 00:27:19 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int handle_input_redirection(t_exec *cmd, int *infile, t_pipex_data *data)
{
	(void)data;
	if (*infile != -1)
		close(*infile);
	*infile = open(cmd->value, O_RDONLY);
	if (*infile < 0)
	{
		cleanup_child_fds(data);
		perror(cmd->value);
		return (0);
	}
	return (0);
}

int handle_output_redirection(t_exec *cmd, int *outfile, t_pipex_data *data)
{
	if (*outfile != -1)
		close(*outfile);
	*outfile = open(cmd->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*outfile < 0)
	{
		perror(cmd->value);
		cleanup_child_fds(data);
		return (-1);
	}
	return (0);
}

int handle_append_redirection(t_exec *cmd, int *outfile, t_pipex_data *data)
{
	if (*outfile != -1)
		close(*outfile);
	*outfile = open(cmd->value, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (*outfile < 0)
	{
		cleanup_child_fds(data);
		perror(cmd->value);
		return (-1);
	}
	return (0);
}

int handle_file_redirection(t_exec *cmd, int *infile, int *outfile,
							t_pipex_data *data)
{
	while (cmd)
	{
		if (cmd->type != COMMAND)
		{
			if (cmd->type == IN_FILE)
			{
				if (handle_input_redirection(cmd, infile, data) == -1)
					return (-1);
			}
			else if (cmd->type == OUT_FILE)
			{
				if (handle_output_redirection(cmd, outfile, data) == -1)
					return (-1);
			}
			else if (cmd->type == APPEND)
			{
				if (handle_append_redirection(cmd, outfile, data) == -1)
					return (-1);
			}
		}
		cmd = cmd->next;
	}
	return (0);
}
