/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:02:07 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/18 20:49:57 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"


static void	run_child_process(t_env **env, char **cmd_argv)
{
	char	**envp;

	envp = ft_env_create_2d(*env);
	execute_cmd(cmd_argv, envp);
	exit(127);
}

static int	retrieve_exit_status(int status)
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

void	execution_cmd(char **cmd, t_env **env, int *exit_status)
{
	char		**cmd_argv;
	pid_t		pid;

	cmd_argv = cmd;
	if (!cmd_argv || !(*cmd_argv))
		return (ft_print_err("cmd_argv is NULL\n"));
	if (ft_execute_builtins(cmd_argv, env, exit_status) == SUCCESS)
		return ;
	pid = fork();
	if (pid < 0)
	{
		ft_print_err("Fork Error\n");
		return ;
	}
	if (pid == 0)
		run_child_process(env, cmd_argv);
	waitpid(pid, exit_status, 0);
	*exit_status = retrieve_exit_status(*exit_status);
}
