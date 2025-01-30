/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:38:30 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/30 22:16:27 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void exit_the_shell(int state)
{
    ft_puterr(state);
    ft_malloc(-1);
    exit(0);
}

char *prompt(char *cli)
{
	char *s;
	s = readline(cli);
    if (!s)
        return (NULL);
    if (ft_strncmp(s, "exit", 4) == 0 && ft_strlen(s) == 4)
        exit_the_shell(0);
    return (free(s), NULL);
}    

void ft_sighandler(int sig)
{
    if (sig == SIGINT || sig == SIGQUIT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

