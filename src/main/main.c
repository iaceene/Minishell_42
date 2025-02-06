/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:48:34 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/31 18:42:28 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    clear_terminal(void)
{
    write(1, "\033[H\033[J", 6);;
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    int err;
    t_data data;

    clear_terminal();
    data.env = env; 
    signal(SIGINT, ft_sighandler);
    signal(SIGQUIT, ft_sighandler);
    while (1)
    {
        data.prompt = prompt(env);
		err = parser(&data);
        if (err == 0)
            printf ("executed !\n");
        else
            ft_puterr(14);
    }
    return (0);
}
