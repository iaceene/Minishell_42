/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:43:44 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/23 11:19:26 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

static int	g_herdocsing;

int	ft_get_signum(void)
{
	return (g_herdocsing);
}

void	ft_sighandler(int sig)
{
	if (sig == SIGINT)
		g_herdocsing++;
	if (sig == SIGINT || sig == SIGQUIT)
	{
		rl_on_new_line();
		if (SIGINT == sig)
			write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	heredoc_child_process(t_herdoc lst)
{
	char	*prom;
	int		fd;
	char	*tmp;

	signal(SIGINT, herdoc_sig);
	signal(SIGQUIT, SIG_IGN);
	fd = open(lst.file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fd < 0)
		return (ft_malloc(-1), exit(130), 1);
	while (1)
	{
		prom = readline("> ");
		if (!prom)
			break ;
		tmp = prom;
		prom = ft_strdup(prom);
		free(tmp);
		if (is_same(prom, lst.exit))
			break ;
		ft_write(fd, expand_heredoc(prom, lst.head, lst.flag,
				lst.exit_state));
	}
	ft_malloc(-1);
	close(fd);
	exit(0);
}

void	def_sig(int sig)
{
	if (sig == SIGINT)
		g_herdocsing++;
}

int	open_herdoc(t_herdoc lst)
{
	pid_t	pid;
	int		last;
	int		status;

	signal(SIGINT, def_sig);
	signal(SIGQUIT, SIG_IGN);
	last = g_herdocsing;
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
		waitpid(pid, &status, 0);
		if (last - g_herdocsing != 0)
		{
			lst.data->exe_state = 130;
			return (-99);
		}
		return (0);
	}
}
