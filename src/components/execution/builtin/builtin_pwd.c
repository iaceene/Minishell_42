/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:05:05 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/27 13:06:31 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

char	*ft_get_cwd(char *tojoin, int i)
{
	char		cwd[MAXPATHLEN];
	static char	save_cwd[MAXPATHLEN];

	if (getcwd(cwd, MAXPATHLEN) != NULL)
		ft_strlcpy(save_cwd, cwd, MAXPATHLEN);
	else if (i == 1)
	{
		ft_strlcat(save_cwd, "/", MAXPATHLEN);
		ft_strlcat(save_cwd, tojoin, MAXPATHLEN);
	}
	return (ft_strdup(save_cwd));
}

void	builtin_pwd(void)
{
	char	*cwd;

	cwd = ft_get_cwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
}
