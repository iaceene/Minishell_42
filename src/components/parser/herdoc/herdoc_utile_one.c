/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utile_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 03:15:38 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/19 18:20:26 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

bool	will_expanded(char *s)
{
	if (find_it(s, '\'') || find_it(s, '"'))
		return (false);
	return (true);
}

void	ft_write(int fd, char *buffer)
{
	int			i;

	if (!buffer || fd == -1)
		return ;
	i = 0;
	while (buffer[i])
	{
		write(fd, buffer + i, 1);
		i++;
	}
	write(fd, "\n", 1);
}

char	*generate_random_name(void)
{
	char			*name;
	int				fd;
	unsigned char	*tmp;
	int				i;

	i = 0;
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

int	open_heredoc_file(char *file_name, int *fd2)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
	*fd2 = open(file_name, O_RDONLY);
	if (unlink(file_name) != 0)
		return (close(fd), close(*fd2), -1);
	if (fd == -1 || *fd2 == -1)
		return (close(fd), close(*fd2), -1);
	return (fd);
}

char	*get_herdoc_fd(t_env *env, char *exit, bool f, int ex_s)
{
	t_herdoc	lst_herdoc;
	char		*file_name;

	file_name = generate_random_name();
	if (!file_name)
		return (NULL);
	lst_herdoc.file_name = file_name;
	lst_herdoc.exit = exit;
	lst_herdoc.head = env;
	lst_herdoc.exit_state = ex_s;
	lst_herdoc.flag = f;
	lst_herdoc.data = env->data;
	if (open_herdoc(lst_herdoc) == -99)
		return (NULL);
	return (file_name);
}
