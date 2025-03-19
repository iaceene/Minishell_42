/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:43:44 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/26 03:15:25 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

void sigint_handler(int signo)
{
	(void)signo;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
	exit(130);
}

int heredoc_child_process(t_herdoc lst)
{
    char *prom;
    
    signal(SIGINT, sigint_handler);
    
	while (1)
	{
		prom = readline("> ");
		if (!prom || (prom && !ft_strncmp(prom, lst.exit, ft_strlen(prom))
			&& ft_strlen(prom) == ft_strlen(lst.exit)))
			break ;
		ft_write(lst.fd, expand_heredoc(prom, lst.head, lst.flag, lst.exit_state));
		free(prom);
	}
    free(prom);
    return (0);
}


int open_herdoc(t_herdoc lst)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
	{
        perror("fork failed");
        return -1;
    }
    if (pid == 0)
        return (heredoc_child_process(lst));
    else
	{
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
            return -99;
        return 0;
    }
}
