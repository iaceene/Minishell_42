/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:55:03 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/26 10:11:44 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

void ft_free_string(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	return;
}

void error_and_exit(const char *str, int exite)
{
	write(2, str, ft_strlen(str));
	exit(exite);
}

void cleanup_shell(t_shell *shell)
{
    if (shell->commands)
	{
		int	i = 0;
        while (i < shell->num_cmds)
		{
            if (shell->commands[i].args)
                free(shell->commands[i].args);
            if (shell->commands[i].path)
                free(shell->commands[i].path);
			i++;
        }
        free(shell->commands);
    }

    if (shell->redirect)
	{
        if (shell->redirect->infile)
            free(shell->redirect->infile);
        if (shell->redirect->outfile)
            free(shell->redirect->outfile);
        free(shell->redirect);
    }
}

