/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:02:07 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/08 10:17:29 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static void run_child_process(t_env **env, char **cmd_argv)
{
    char **envp;
    envp = ft_env_create_2d(*env);
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    execute_cmd(cmd_argv, envp);
    perror("execve failed for child1");
    exit(127);
}

static int retrieve_exit_status(int status)
{
    if (WIFSIGNALED(status))
    {
        if (WTERMSIG(status) == SIGINT)
        {
            write(1, "\n", 1);
            return (130);
        }
        if (WTERMSIG(status) == SIGQUIT)
        {
            write(1, "Quit: 3\n", 8);
            return (131);
        }
    }
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (1);
}

void execution_cmd(char *cmd, t_env **env, int *exit_status)
{
    // char **cmd_argv;
    char **cmd_argv = ft_split(cmd, ' ');
    pid_t pid;
    struct termios state;
    // printf("cmd: %s\n", cmd);
    // cmd_argv = expand_input(cmd, *env, *exit_status);
    // printf("sor [0]: %s\n", cmd_argv[0]);
    // printf("sor [0]: %s\n", cmd_argv[1]);
    if (!cmd_argv || !(*cmd_argv))
        return (ft_print_err("cmd_argv is NULL\n"));
    if (ft_execute_builtins(cmd_argv, env, exit_status) == SUCCESS)
        return;
    signal(SIGINT, ft_sighandler);
    signal(SIGQUIT, ft_sighandler);
    if ((pid = fork()) < 0)
    {
        ft_print_err("Fork Error\n");
        return;
    }
    if (pid == 0)
        run_child_process(env, cmd_argv);
    waitpid(pid, exit_status, 0);
    if (WIFSIGNALED(*exit_status) && WTERMSIG(*exit_status) == SIGQUIT)
        tcsetattr(STDOUT_FILENO, TCSANOW, &state);
    *exit_status = retrieve_exit_status(*exit_status);
    signal(SIGINT, ft_sighandler);
    signal(SIGQUIT, ft_sighandler);
}
