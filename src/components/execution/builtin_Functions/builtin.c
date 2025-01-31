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

int ft_isspace(int c)
{
    return (c == ' '  || c == '\t' || c == '\n' ||
            c == '\r' || c == '\v' || c == '\f');
}


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
void execute_builtin(char **args, char ***env)
{
    if (ft_strncmp(args[0], "echo", 4) == 0)
        builtin_echo(args);
    if (ft_strncmp(args[0], "cd", 2) == 0)
        builtin_cd(args, env);
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
}

int main(int argc, char **argv, char **envp)
{
    char *line = NULL;
    size_t len = 0;
    char **env = NULL;

    int env_count = 0;
    while (envp[env_count])
        env_count++;
    env = malloc(sizeof(char *) * (env_count + 1));
    for (int i = 0; i < env_count; i++)
    {
        env[i] = strdup(envp[i]);
    }
    env[env_count] = NULL;

    while (1)
    {
        printf("minishell> ");
        if (getline(&line, &len, stdin) == -1)
        {
            perror("getline");
            break;
        }

        // Remove the newline character
        line[strcspn(line, "\n")] = '\0';
        if (is_empty(line))
            continue;

        // Split input into arguments
        char **args = ft_split(line, ' ');
        if (!args[0])
            continue;

        // Check for builtins
        execute_builtin(args, &env);

        // Free memory
        ft_free_string(args);
    }

    free(line);
    ft_free_string(env);
    return 0;
}
