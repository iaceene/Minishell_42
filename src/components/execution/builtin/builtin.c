/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:26:52 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/27 13:03:10 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int is_empty(const char *str)
{
    if (!str || *str == '\0')
        return 1;

    while (*str)
    {
        if (!ft_isspace((unsigned char)*str))
            return 0;
        str++;
    }
    return 1;
}
void execute_builtin(t_shell *shell)
{
    if (!shell || !shell->commands || !shell->commands[0].args || !shell->commands[0].args[0])
        return;

    char **args = shell->commands[0].args;
    char ***env = &shell->env;
    // char **args1 = shell->commands[1].args;
    if (ft_strncmp(args[0], "echo", 4) == 0)
        builtin_echo(args);
    // else if (ft_strncmp(args[0], "cd", 2) == 0)
        // builtin_cd(args, enlz);
    else if (ft_strncmp(args[0], "pwd", 3) == 0)
        builtin_pwd();
    else if (ft_strncmp(args[0], "export", 6) == 0)
        builtin_export(args, env);
    else if (ft_strncmp(args[0], "unset", 5) == 0)
        builtin_unset(args, env);
    else if (ft_strncmp(args[0], "env", 3) == 0)
        builtin_env(*env);
    else if (ft_strncmp(args[0], "exit", 4) == 0)
        builtin_exit(args);
    else
    {
        write(2, "Command not found: ", 19);
        write(2, args[0], ft_strlen(args[0]));
        write(2, "\n", 1);
    }
    // if (ft_strncmp(args1[0], "pwd", 3) == 0)
    //     builtin_pwd();
}
