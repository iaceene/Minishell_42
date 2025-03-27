/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:43:44 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/27 01:07:34 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

static int	g_herdocsing;

void	ft_sighandler(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		g_herdocsing++;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	herdoc_signal(int signo)
{
	(void)signo;
	g_herdocsing = 1;
	rl_on_new_line();
	exit(130);
}

int	heredoc_child_process(t_herdoc lst)
{
	char	*prom;

	signal(SIGINT, herdoc_signal);
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

int	open_herdoc(t_herdoc lst)
{
	pid_t	pid;
	int		last;
	int		status;

	pid = fork();
	last = g_herdocsing;
	if (pid == -1)
	{
		perror("fork failed");
		return (-1);
	}
	if (pid == 0)
		return (heredoc_child_process(lst));
	else
	{
		waitpid(pid, &status, 0);
		if (last - g_herdocsing != 0)
			return (-99);
		return (0);
	}
}
