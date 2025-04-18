/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:44:11 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/31 17:52:04 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

char	*ft_join_params(char *user, char *dis)
{
	char	*cli;

	if (!user || !dis)
		return (exit_the_shell(11), NULL);
	cli = ft_strjoin(user, "\033[32m@\033[0m");
	cli = ft_strjoin(cli, dis);
	cli = ft_strjoin(cli, "\033[32m $ \033[0m");
	return (cli);
}
