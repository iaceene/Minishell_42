/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:02:07 by iezzam            #+#    #+#             */
/*   Updated: 2025/04/08 21:49:50 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

static void	run_child_process(t_env **env, char **cmd_argv, int *exit_status)
{
	char	**envp;

	envp = ft_env_create_2d(*env);
	execute_cmd(cmd_argv, envp, exit_status);
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
	char			**cmd_argv;
	pid_t			pid;
	t_pipex_data	data;

	data.f_fd = 1;
	data = (t_pipex_data){-1, -1, {-1, -1}, -1, 1, 0, 0};
	cmd_argv = cmd;
	if (!cmd_argv || !(*cmd_argv))
	{
		*exit_status = 0;
		return ;
	}
	if (ft_execute_builtins(cmd_argv, env, exit_status, &data) == SUCCESS)
	{
		*exit_status = 0;
		return ;
	}
		signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		(ft_print_err("Fork Error\n"), *exit_status = 1, exit(1));
	if (pid == 0)
		run_child_process(env, cmd_argv, exit_status);
	waitpid(pid, exit_status, 0);
	*exit_status = retrieve_exit_status(*exit_status);
}
