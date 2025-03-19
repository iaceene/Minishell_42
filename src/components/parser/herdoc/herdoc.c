/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:43:44 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/18 22:46:03 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

bool	will_expanded(char *s)
{
	if (find_it(s, '\'') || find_it(s, '"'))
		return (false);
	return (true);
}

char	*expand_heredoc(char *prom, t_env *env, bool f)
{
	char	*res;

	if (!prom || !f)
		return (prom);
	(void)env;
	printf("expand\n");
	res = ft_strdup("expand");
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

int	get_herdoc_fd(t_env *env, char *exit, bool f)
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
		ft_write(fd, expand_heredoc(prom, env, f));
	}
	close(fd);
	return (fd2);
}

char	*remove_qoats(char *s)
{
	char	*result;
	int		i;
	int		j;
	bool	in_single_quotes;
	bool	in_double_quotes;

	if (!s)
		return (NULL);
	result = ft_malloc(strlen(s) + 1);
	i = 0;
	j = 0;
	in_single_quotes = false;
	in_double_quotes = false;
	while (s[i])
	{
		if (s[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (s[i] == '\"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else
			result[j++] = s[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

t_cmd	*new_cmd_hered(char **val)
{
	t_cmd	*ret;

	printf("this is the string %s\n", val[0]);
	ret = ft_malloc(sizeof(t_cmd));
	ret->cmd = val;
	ret->type = COMMAND;
	ret->next = NULL;
	ret->value = NULL;
	return (ret);
}

int	herdoc(t_env *env, t_cmd *commnd, t_cmd **head, char *exit)
{
	int		fd;
	bool	qoated;
	char	**arg;

	fd  = -1;
	qoated = will_expanded(exit);
	set_space_zero_qoats(exit);
	arg = ft_split(exit, ' ');
	if (!arg)
		return (-1);
	set_zero_space(arg);
	exit = remove_qoats(arg[0]);
	if (commnd)
		commnd->cmd = join_args_adv(commnd->cmd, arg);
	// else if (arg + 1 && *(arg + 1))
	else if (arg && *(arg + 1))
		add_to_cmd(head, new_cmd_hered(arg + 1));
	fd = get_herdoc_fd(env, exit, qoated);
	return (fd);
}
