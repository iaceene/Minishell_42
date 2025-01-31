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

void print_cli(char **env)
{
    static char *cli;
    static int  i;
    
    if (i == 0)
        cli = ft_get_cli(env);
    ft_putstr(cli);
    i++;
}

char *prompt(char **env)
{
    char *s;
    print_cli(env);
    s = get_next_line(0);
    if (!s)
        exit_the_shell(0);
    if (ft_strncmp(s, "exit\n", 5) == 0 && ft_strlen(s) == 5)
        exit_the_shell(0);
    return (s);
} 

void ft_sighandler(int sig)
{
    if (sig == SIGINT || sig == SIGQUIT)
    {
        write(1, "\n", 1);
        print_cli(NULL);
    }
}

