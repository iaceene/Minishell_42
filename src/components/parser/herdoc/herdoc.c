/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:43:44 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/18 20:17:37 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

bool	will_expanded(char *s)
{
	if (find_it(s, '\'') || find_it(s, '"'))
		return (false);
	return (true);
}

size_t	get_var_len(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] && (isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}

char	*get_env_val(char *var, t_env *env)
{
	while (env)
	{
		if (strcmp(env->key, var) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	append_str(char **res, size_t *len, char *str, size_t n)
{
	*res = realloc(*res, *len + n + 1);
	strncat(*res, str, n);
	*len += n;
}

char	*expand_heredoc(char *prom, t_env *env, char *exit)
{
	char	*res;
	size_t	i;
	size_t	len;

	if (!prom || !find_it(prom, '$') || !will_expanded(exit))
		return (prom);
	res = malloc(1);
	res[0] = '\0';
	i = 0;
	len = 0;
	while (prom[i])
	{
		if (prom[i] == '$' && (isalnum(prom[i + 1]) || prom[i + 1] == '_'))
		{
			append_str(&res, &len, get_env_val(prom + i + 1, env),
				get_var_len(prom + i + 1));
			i += get_var_len(prom + i + 1) + 1;
		}
		else
			append_str(&res, &len, &prom[i++], 1);
	}
	return (res);
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
	int			fd2;

	file_name = generate_file();
	if (!file_name)
		return (-1);
	fd = open(file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
	fd2 = open(file_name, O_RDONLY);
	if (unlink(file_name) != 0)
		return (-1);
	if (fd == -1)
		return (-1);
	while (1)
	{
		prom = readline("> ");
		if (!prom ||
			(prom && !ft_strncmp(prom, exit, ft_strlen(prom))
			&& ft_strlen(prom) == ft_strlen(exit)))
			break ;
		ft_write(fd, expand_heredoc(prom, env, exit));
	}
	close(fd);
	return (fd2);
}
