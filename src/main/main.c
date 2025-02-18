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

void clear_terminal(void)
{
	write(1, "\033[H\033[J", 6);
}

static void ft_init(t_tool *tool, char **env)
{
	tool->grbg = NULL;
	tool->env = ft_env_create(env);
	tool->env->a_ven = ft_env_create_2d(tool->env);
	tool->err = 0;
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_data data;
	t_tool tool;

    clear_terminal();
    data.env = env;
    signal(SIGINT, ft_sighandler);
    signal(SIGQUIT, ft_sighandler);
	ft_init(&tool, env);
    while (1)
    {
        data.prompt = prompt(env);
        if (!data.prompt[0])
            ft_puterr(32);
		else if (parser(&data))
			execution(&data.head, &tool.env, &tool.err);
        else
            ft_puterr(14);
    }
    return (0);
}
