/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utile_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:15:38 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/20 03:17:02 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

bool	will_expanded(char *s)
{
	if (find_it(s, '\'') || find_it(s, '"'))
		return (false);
	return (true);
}

char	*expand_heredoc(char *prom, t_env *env, bool f, int exit)
{
	if (!prom || !f)
		return (prom);
	return (expander(prom, env, exit));
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

char	*generate_file(void)
{
	char			*name;
	int				fd;
	unsigned char	*tmp;
	int				i;

	i  = 0;
	fd = open("/dev/random", 0);
	if (fd == -1)
		return (NULL);
	tmp = ft_malloc(21 * sizeof(unsigned char));
	if (read(fd, tmp, 20) != 20)
		return (close(fd), NULL);
	close(fd);
	while (i < 20)
	{
		tmp[i] = (tmp[i] % 26) + 'A';
		i++;	
	}
	tmp[i] = '\0';
	name = ft_strjoin("/tmp/", ft_strjoin(".", (char *)tmp));
	return (name);
}

int	get_herdoc_fd(t_env *env, char *exit, bool f, int ex_s)
{
	char		*prom;
	char		*file_name;
	int 		fd;
	int			fd2;

	file_name = generate_file();
	if (!file_name)
		return (-1);
	fd = open(file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
	fd2 = open(file_name, O_RDONLY);
	if (unlink(file_name) != 0)
		return (close(fd), close(fd2), -1);
	if (fd == -1)
		return (close(fd), close(fd2), -1);
	while (1)
	{
		prom = readline("> ");
		if (!prom ||
			(prom && !ft_strncmp(prom, exit, ft_strlen(prom))
			&& ft_strlen(prom) == ft_strlen(exit)))
			break ;
		ft_write(fd, expand_heredoc(prom, env, f, ex_s));
	}
	close(fd);
	return (fd2);
}
