/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cli.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:42:28 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/31 18:14:52 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

char	*ft_get_user(char **env)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (!*env)
		return (0);
	while (env[i])
	{
		if (ft_strstr(env[i], "LOGNAME"))
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 0)
		return (NULL);
	return (ft_strdup(ft_strchr(env[i], '=')));
}

char	**ft_get_sission(char **env)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], "SESSION_MANAGER"))
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 0)
		return (NULL);
	return (ft_split(ft_strchr(env[i], '/'), '.'));
}

char	*ft_get_cli(char **env)
{
	char	*user;
	char	**desktop;

	if (!*env)
		return (ft_strdup("user42@1337 $ "));
	user = ft_get_user(env);
	if (!user)
		user = ft_strdup("user42");
	desktop = ft_get_sission(env);
	if (!desktop)
		return (ft_join_params(user, ft_strdup("1337")));
	else
		return (ft_join_params(user, desktop[0]));
	return (NULL);
}
