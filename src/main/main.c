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


void init_shell(t_shell *shell)
{
    shell->num_cmds = 1;
    shell->last_exit = 0;
    shell->in_pipe = 0;

    shell->commands = calloc(shell->num_cmds, sizeof(t_command));
    shell->redirect = calloc(1, sizeof(t_redirect));
    shell->commands = ft_malloc(shell->num_cmds * sizeof(t_command));
    shell->redirect = ft_malloc(1 *sizeof(t_redirect));

    shell->commands[0].args = ft_malloc(2 * sizeof(char *));
    shell->commands[0].args[0] = ft_strdup("pwd");
    // shell->commands[0].args[1] = ft_strdup("-la");
    shell->commands[0].args[1] = NULL;
    shell->commands[0].append = 0;

    // shell->commands[1].args = calloc(2, sizeof(char *));
    // shell->commands[1].args[0] = ft_strdup("cat");
    // shell->commands[1].args[1] = NULL;
    // shell->commands[1].path = "/bin/cat";
    // shell->commands[1].append = 0;

    // shell->commands[2].args = calloc(2, sizeof(char *));
    // shell->commands[2].args[0] = ft_strdup("cat");
    // shell->commands[2].args[1] = NULL;
    // shell->commands[2].path = "/bin/cat";
    // shell->commands[2].append = 0;

    // shell->commands[3].args = calloc(3, sizeof(char *));
    // shell->commands[3].args[0] = ft_strdup("ls");
    // shell->commands[3].args[1] = ft_strdup("-la");
    // shell->commands[3].args[2] = NULL;
    // shell->commands[3].path = "/bin/ls";
    // shell->commands[3].append = 0;

    shell->redirect->infile = NULL;
    shell->redirect->outfile = NULL;
}


int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_data data;

    data.shell = ft_malloc(sizeof(t_shell));
    if (!data.shell)
    {
        write(2, "Error: Failed to allocate memory for shell.\n", 45);
        return (1);
    }

    data.env_var = ft_env_create(env);
    data.env = convert_env_to_array(data.env_var);
    data.shell->env = data.env;

    int i = 0;
    while (data.env[i])
    {
        fprintf(stderr, "+++++++++++++++++++++data.env[%d]: %s\n", i, data.env[i]);
        i++;
    }

    int err;

    clear_terminal();
    signal(SIGINT, ft_sighandler);
    signal(SIGQUIT, ft_sighandler);
    while (1)
    {
        data.prompt = prompt(data.env);
		err = parser(&data);
        // if (err == 1)
            execution(data.shell);
        // else
            ft_puterr(err);
    }
    return (0);
}
