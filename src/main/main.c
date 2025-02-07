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
#include "../../include/execution.h"
#include "../../include/parser.h"

void clear_terminal(void)
{
	write(1, "\033[H\033[J", 6);
}


static void ft_init(t_tool *tool, int ac, char **av, char **env)
{
	(void)(ac);
	(void)(av);
	tool->grbg = NULL;
	tool->env = ft_env_create(env);
	tool->env->a_ven = ft_env_create_2d(tool->env);
	tool->err = 0;
}


// int main(int ac, char **av, char **env)
// {
// 	t_data data;
// 	t_tree *tree = ft_malloc(sizeof(t_tree));
// 	t_tool tool;
// 	int err;

// 	clear_terminal();
// 	signal(SIGINT, ft_sighandler);
// 	signal(SIGQUIT, ft_sighandler);
// 	ft_init(&tool, ac, av, env);
// 	if (!isatty(0))
// 		return (printf("tty required!\n"), 1);

// 	while (1)
// 	{
// 		data.prompt = prompt(tool.env->a_ven);

// 		char *input = data.prompt;

// 		tree->value = input;

// 		err = parser(&data);

// 		execution(tree, &tool.env, &tool.err);
// 	}
// 	return (0);
// }


int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    int err;
    t_data data;
	t_tool tool;

    clear_terminal();
    data.env = env; 
    signal(SIGINT, ft_sighandler);
    signal(SIGQUIT, ft_sighandler);
	ft_init(&tool, ac, av, env);
    while (1)
    {
        data.prompt = prompt(env);
		err = parser(&data);
		if (err == 0)
			execution(data.head, &tool.env, &tool.err);
        else
            ft_puterr(14);
    }
    return (0);
}
