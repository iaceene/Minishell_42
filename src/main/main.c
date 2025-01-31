/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:48:34 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/31 17:20:28 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void init_shell(t_shell *shell, char **envp, int ac, char **av)
{
    t_env *env_list;
    env_list = ft_env_create(envp);
    shell->env = convert_env_to_array(env_list);
    (void)ac;
    (void)av;
}

int main(int ac, char **av, char **env)
{
    t_data data;

    data.env = env;
    data.env_var = ft_env_create(env);
    clear_terminal();
    signal(SIGINT, ft_sighandler);
    signal(SIGINT, ft_sighandler);
    signal(SIGQUIT, ft_sighandler);
    while (1)
        prompt(env);
    return (0);
}
