/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:20:54 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/02 20:43:39 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int	count_env_list(t_env *env_list)
{
	int		count;
	t_env	*temp;

	if (!env_list)
		return (0);
	count = 0;
	temp = env_list;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

char	*ft_env_search(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	**convert_env_to_array(t_env *env_list)
{
	int		count;
	t_env	*temp;
	int		i;
	char	**env_array;

	count = count_env_list(env_list);
	env_array = ft_malloc((count + 1) * sizeof(char *));
	temp = env_list;
	i = 0;
	while (i < count)
	{
		env_array[i] = ft_strjoin(temp->key, "=");
		env_array[i] = ft_strjoin(env_array[i], temp->value);
		temp = temp->next;
		i++;
	}
	env_array[count] = NULL;
	return (env_array);
}
