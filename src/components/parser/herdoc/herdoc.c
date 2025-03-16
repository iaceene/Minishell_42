/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:43:44 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/16 19:29:47 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

char	*expand_herdoc(char *prom, t_env *env)
{
	if (!prom || !find_it(prom, '$'))
		return (prom);
	(void)env;
	return (prom);
}

void	ft_write(int fd, char *buffer)
{
	int			i;
	static	int k;

	if (!buffer || fd == -1)
		return;
	i = 0;
	if (k != 0)
		write(fd, "\n", 1);
	while (buffer[i])
	{
		write(fd, buffer + i, 1);
		i++;
	}
	k++;
}

char	*herdoc(t_env *env, char *exit)
{
	char		*prom;
	int 		fd;

	fd = open("test.txt", O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fd == -1)
		return (NULL);
	while (1)
	{
		prom = readline("> ");
		if (!prom ||
			(prom && !ft_strncmp(prom, exit, ft_strlen(prom))
			&& ft_strlen(prom) == ft_strlen(exit)))
			break ;
		ft_write(fd, expand_herdoc(prom, env));
	}
	close(fd);
	return (NULL);
}
