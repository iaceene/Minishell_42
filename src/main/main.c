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

void    clear_terminal(void)
{
    write(1, "\033[H\033[J", 6);;
}


static void	ft_init(t_tool *tool, t_tree *trrep, int ac, char **av, char **env)
{
	(void)(ac);
	(void)(av);
	tool->grbg = NULL;
	tool->env = ft_env_create(env);
	tool->env->a_ven = ft_env_create_2d(tool->env);
	tool->err = 0;

	trrep->value = "echo /home/iezzam";
	trrep->prio = 0;
	trrep->read = 0;
	trrep->type = 0;
	trrep->right = NULL;
	trrep->left = NULL;	
		// execution_cmd("pwd", &tool->env, &tool->err);

}


int main(int ac, char **av, char **env)
{
    t_data data;
    t_tree tree;
    t_tool tool;
	int err;

    clear_terminal();
    signal(SIGINT, ft_sighandler);
    signal(SIGQUIT, ft_sighandler);
    ft_init(&tool, &tree, ac, av, env);
	if (!isatty(0))
		return (printf("tty required!\n"), 1);

    while (1)
    {
        data.prompt = prompt(tool.env->a_ven);
		err = parser(&data);
		// if (err == 0)
       	execution(&tree, &tool.env, &tool.err);
		// else
		// {
		// 	ft_print_err("Parsing error\n");
		// 	ft_puterr(err);
		// }
	}
    return (0);
}
































// void init_shell(t_shell *shell)
// {
//     shell->num_cmds = 1;
//     shell->last_exit = 0;
//     shell->in_pipe = 0;

//     shell->commands = calloc(shell->num_cmds, sizeof(t_command));
//     shell->redirect = calloc(1, sizeof(t_redirect));
//     shell->commands = ft_malloc(shell->num_cmds * sizeof(t_command));
//     shell->redirect = ft_malloc(1 *sizeof(t_redirect));

//     shell->commands[0].args = ft_malloc(2 * sizeof(char *));
//     shell->commands[0].args[0] = ft_strdup("pwd");
//     shell->commands[0].args[1] = NULL;
//     shell->commands[0].append = 0;

// }