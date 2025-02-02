/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 07:57:13 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/29 10:50:39 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	free_env(t_env *env_list)
{
	t_env	*temp;

	while (env_list)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

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



t_env	*ft_env_create(char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	int		i;

	if (!envp)
		return (NULL);
	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->key = ft_strdup(ft_strtok(envp[i], "="));
		new_node->value = ft_strdup(ft_strtok(NULL, "\n"));
		if (!new_node->key || !new_node->value)
		{
			free(new_node);
			return (NULL);
		}
		new_node->next = env_list;
		env_list = new_node;
		i++;
	}
	return (env_list);
}

char	**convert_env_to_array(t_env *env_list)
{
	int		count;
	t_env	*temp;
	int		i;
	char	*temp_value;
	char	**env_array;

	count = count_env_list(env_list);
	env_array = malloc((count + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	temp = env_list;
	i = 0;
	while (i < count)
	{
		env_array[i] = ft_strjoin(temp->key, "=");
		temp_value = ft_strjoin(env_array[i], temp->value);
		env_array[i] = temp_value;
		temp = temp->next;
		i++;
	}
	env_array[count] = NULL;
	return (env_array);
}
