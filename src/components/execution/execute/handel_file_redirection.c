/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_file_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneki <kaneki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 06:22:19 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/18 06:58:32 by kaneki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

void	handle_input_redirection(t_exec *cmd, int *infile)
{
	if (*infile != -1)
		close(*infile);
	*infile = open(cmd->value, O_RDONLY);
	if (*infile < 0)
	{
		write(2, "No such file or directory: ", 27);
		write(2, cmd->value, ft_strlen(cmd->value));
		write(2, "\n", 1);
		exit(1);
	}
}

void	handle_output_redirection(t_exec *cmd, int *outfile)
{
	if (*outfile != -1)
		close(*outfile);
	*outfile = open(cmd->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*outfile < 0)
		error_and_exit("Failed to open output file", 1);
}

void	handle_append_redirection(t_exec *cmd, int *outfile)
{
	if (*outfile != -1)
		close(*outfile);
	*outfile = open(cmd->value, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (*outfile < 0)
		error_and_exit("Failed to open output file for append", 1);
}

void	handle_file_redirection(t_exec *cmd, int *infile, int *outfile)
{
	while (cmd)
	{
		if (cmd->type != COMMAND)
		{
			if (cmd->type == IN_FILE)
				handle_input_redirection(cmd, infile);
			else if (cmd->type == OUT_FILE)
				handle_output_redirection(cmd, outfile);
			else if (cmd->type == APPEND)
				handle_append_redirection(cmd, outfile);
		}
		cmd = cmd->next;
	}
}
