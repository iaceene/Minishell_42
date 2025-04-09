/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:43:44 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/09 17:23:54 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

static int	g_herdocsing;

void	ft_sighandler(int sig)
{
	if (sig == SIGINT)
		g_herdocsing++;
	if (sig == SIGINT || sig == SIGQUIT)
	{
		rl_on_new_line();
		if (SIGINT == sig)
			write(1, "\n", 1);
		else
			write(1, "\033[K", 4);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	herdoc_sig(int sig)
{
	if (sig == SIGINT)
		exit(130);
	else
	{
		write(1, "\033[K", 4);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	heredoc_child_process(t_herdoc lst)
{
	char	*prom;

	signal(SIGINT, herdoc_sig);
	signal(SIGQUIT, herdoc_sig);
	while (1)
	{
		prom = readline("> ");
		if (!prom || (prom && !ft_strncmp(prom, lst.exit, ft_strlen(prom))
				&& ft_strlen(prom) == ft_strlen(lst.exit)))
			break ;
		ft_write(lst.fd, expand_heredoc(prom, lst.head, lst.flag,
				lst.exit_state));
		free(prom);
	}
	free(prom);
	exit(0);
}

void	def_sig(int sig)
{
	if (sig)
		return ;
}

int	open_herdoc(t_herdoc lst)
{
	pid_t	pid;
	int		last;
	int		status;

	signal(SIGINT, def_sig);
	signal(SIGQUIT, def_sig);
	last = g_herdocsing;
	printf("%d\n", last);
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return (-1);
	}
	if (pid == 0)
		return (heredoc_child_process(lst));
	else
	{
	printf("%d\n", last);
		waitpid(pid, &status, 0);
		if (last - g_herdocsing != 0)
		{
			return (-99);
		}
		return (0);
	}
}
