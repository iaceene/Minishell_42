/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:43:44 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/16 23:43:12 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

char	*expand_herdoc(char *prom, t_env *env)
{
	if (!prom || !find_it(prom, '$'))
		return (prom);
	(void)env;
	// to do 
	// check this rule also '' if there is a sing or dob in delemter!
	// this will not be expanded!
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

int	herdoc(t_env *env, char *exit)
{
	char		*prom;
	char		*file_name;
	int 		fd;

	file_name = generate_file();
	if (!file_name)
		return (-1);
	fd = open(file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fd == -1)
		return (-1);
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
	fd = open(file_name, O_RDONLY);
	if (unlink(file_name) != 0)
		return (-1);
	return (fd);
}
