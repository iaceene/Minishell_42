/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_file_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:22:19 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/19 20:41:04 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	handle_input_redirection(t_exec *cmd, int *infile, t_pipex_data *data)
{
	if (*infile != -1)
		close(*infile);
	(void)data;
	if (access(cmd->value, R_OK) !=  0)
	{
		perror(cmd->value);
		// cleanup_child_fds(data); // zidha
		return ;
	}
	*infile = open(cmd->value, O_RDONLY);
}

void	handle_output_redirection(t_exec *cmd, int *outfile, t_pipex_data *data)
{
	(void)data;
	*outfile = open(cmd->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*outfile < 0)
	{
		perror(cmd->value);
		cleanup_child_fds(data); // zifdha
		// error_and_exit("Failed to open output file", 1);
	}
}

void	handle_append_redirection(t_exec *cmd, int *outfile, t_pipex_data *data)
{
	*outfile = open(cmd->value, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (*outfile < 0)
	{
		perror("");
		error_and_exit("Failed to open output file for append", 1);
		cleanup_child_fds(data);
	}
}

void	handle_file_redirection(t_exec *cmd, int *infile, int *outfile, \
	t_pipex_data *data)
{
	while (cmd)
	{
		if (cmd->type != COMMAND)
		{
			if (cmd->type == IN_FILE)
				handle_input_redirection(cmd, infile, data);
			else if (cmd->type == OUT_FILE)
				handle_output_redirection(cmd, outfile, data);
			else if (cmd->type == APPEND)
				handle_append_redirection(cmd, outfile, data);
		}
		cmd = cmd->next;
	}
}
