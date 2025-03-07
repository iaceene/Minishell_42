/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:38:30 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/31 18:33:54 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void exit_the_shell(int state)
{
    ft_malloc(-1);
    ft_puterr(state);
    exit(state);
}

void ft_putstr(char *s)
{
    int i = 0;
    while (s[i])
    {
        write(1, &s[i], 1);
        i++;
    }
}

char *prompt(char **env)
{
    char        *s;
    static char *cli;
    static int  i;

    if (i == 0)
        cli = ft_get_cli(env);
    s = readline(cli);
    if (!s)
        exit_the_shell(0);
    if (ft_strncmp(s, "exit", 4) == 0 && ft_strlen(s) == 4)
        exit_the_shell(0);
    i++;
    add_history(s);
    return (s);
} 

void ft_sighandler(int sig)
{
    if (sig == SIGINT || sig == SIGQUIT)
    {
        write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

