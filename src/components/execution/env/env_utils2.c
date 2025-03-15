/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:18:58 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/15 06:45:07 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

static int	ft_env_count(t_env *env)
{
	t_env	*temp;
	int		count;

	count = 0;
	temp = env;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

static char	*ft_create_env_string(t_env *env_node)
{
	int		key_len;
	int		value_len;
	int		len;
	char	*env_str;

	key_len = ft_strlen(env_node->key);
	value_len = ft_strlen(env_node->value);
	len = key_len + value_len + 2;
	env_str = ft_malloc(len * sizeof(char));
	ft_memcpy(env_str, env_node->key, key_len);
	env_str[key_len] = '=';
	ft_memcpy(env_str + key_len + 1, env_node->value, value_len);
	env_str[len - 1] = '\0';
	return (env_str);
}

char	**ft_env_create_2d(t_env *env)
{
	t_env	*temp;
	int		count;
	int		i;
	char	**envp;

	count = ft_env_count(env);
	envp = ft_malloc((count + 1) * sizeof(char *));
	temp = env;
	i = 0;
	while (i < count)
	{
		envp[i] = ft_create_env_string(temp);
		temp = temp->next;
		i++;
	}
	envp[count] = NULL;
	return (envp);
}
