/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:38:30 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/31 18:33:54 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	exit_the_shell(int state)
{
	if (state == 4)
		perror("");
	ft_malloc(-1);
	ft_puterr(state);
	exit(state);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	ft_get_sigin(int *s)
{
	static int	last;
	int			tmp;

	tmp = last;
	last = ft_get_signum();
	if (last - tmp != 0)
		*s = 130;
}

char	*prompt(char **env, int *ex)
{
	char		*s;
	char		*tmp;
	static char	*cli;
	static int	i;

	if (i == 0)
		cli = ft_get_cli(env);
	rl_instream = stdin;
	if (!isatty(STDIN_FILENO))
		exit_the_shell(3);
	ft_get_sigin(ex);
	s = readline(cli);
	ft_get_sigin(ex);
	if (!s)
		exit_the_shell(*ex);
	i++;
	if (s[0])
		add_history(s);
	tmp = ft_strdup(s);
	free(s);
	return (tmp);
}
