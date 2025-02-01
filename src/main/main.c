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

void open_files(t_shell *data, int ac, char **av)
{
    data->redirect->infile = av[1];
    data->redirect->fdin = open(av[1], O_RDONLY, 0644);
    if (data->redirect->fdin == -1)
    {
        write(2, "error open no such file or directory: ", 38);
        write(2, av[1], ft_strlen(av[1]));
        write(2, "\n", 1);
        data->redirect->fdin = STDERR_FILENO;
    }

    data->redirect->outfile = av[ac - 1];
    data->redirect->fdout = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (data->redirect->fdout == -1)
    {
        close_fd(data->redirect);
        error_and_exit("Error opening output file\n", 1);
    }
}


void init_shell(t_shell *shell)
{
    shell->num_cmds = 1;
    shell->last_exit = 0;
    shell->in_pipe = 0;

    shell->commands = ft_malloc(shell->num_cmds * sizeof(t_command));
    shell->redirect = ft_malloc(1 *sizeof(t_redirect));

    shell->commands[0].args = ft_malloc(3 * sizeof(char *));
    shell->commands[0].args[0] = ft_strdup("cd");
    shell->commands[0].args[1] = ft_strdup("..");
    shell->commands[0].args[2] = NULL;
    shell->commands[0].append = 0;

    shell->commands[1].args = ft_malloc(2 * sizeof(char *));
    shell->commands[1].args[0] = ft_strdup("pwd");
    shell->commands[1].args[1] = NULL;
    shell->commands[1].append = 0;

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
        fprintf(stderr, "data.env[%d]: %s\n", i, data.env[i]);
        i++;
    }

    clear_terminal();
    signal(SIGINT, ft_sighandler);
    signal(SIGQUIT, ft_sighandler);

    init_shell(data.shell);

    while (1)
    {
        data.prompt = prompt(data.env);
		parser(&data);
        execution(data.shell);
    }

    return (0);
}
