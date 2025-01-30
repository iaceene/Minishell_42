/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:48:34 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/30 23:07:48 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int main(int ac, char **av, char **env)
{
    t_data data;

    data.env = env;
    
    check_path(&data);
    clear_terminal();
    signal(SIGINT, ft_sighandler);
    signal(SIGQUIT, ft_sighandler);
    while (1)
        prompt(env);
    return (0);
}
