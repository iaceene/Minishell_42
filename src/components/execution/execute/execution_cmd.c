/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:02:07 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/03 10:44:21 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../../include/minishell.h"

static void run_child_process(t_env **env, char **cmd_argv)
{
    char **envp;

    if (!envp || !(*envp))
        return ;
    envp = (*env)->a_ven;
    execute_cmd(cmd_argv, envp);
    perror("execve failed for child1");
    exit(127);
}

static int retrieve_exit_status(int status)
{
    if (WIFSIGNALED(status))
    {
        if (WTERMSIG(status) == SIGINT)
            return (130);
        if (WTERMSIG(status) == SIGQUIT)
            return (131);
    }
    return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
}

void execution_cmd(char *cmd, t_env **env, int *exit_status)
{
    char **cmd_argv;
    pid_t pid;
    struct termios state;
    if (!(cmd_argv = ft_expand(cmd, *env, *exit_status)))
    {
        ft_print_err("ft_expand failed\n");
        return;
    }
    if (ft_execute_builtins(cmd_argv, env, exit_status) == SUCCESS)
        return;
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    tcgetattr(STDOUT_FILENO, &state);
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
    signal(SIGINT, ft_handle_signals);
    signal(SIGQUIT, ft_handle_signals);
}

