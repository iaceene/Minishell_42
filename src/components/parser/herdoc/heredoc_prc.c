/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:43:44 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/26 21:03:04 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

int	g_herdocsing;

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
	return (0);
}

int	open_herdoc(t_herdoc lst)
{
	pid_t	pid;
	int		status;

	pid = fork();
	g_herdocsing = 0;
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
		if (g_herdocsing)
			return (-99);
		return (0);
	}
}
