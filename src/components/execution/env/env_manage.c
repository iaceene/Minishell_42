/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:21:05 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/02 20:42:23 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void	ft_env_delete(t_env **env, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!env || !*env || !key)
		return;
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_env_add(t_env **env, char *key, char *value, int overwrite)
{
	t_env	*new;
	t_env	*current;

	if (!env || !key || !value)
		return;
	current = *env;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
		{
			if (overwrite)
			{
				free(current->value);
				current->value = ft_strdup(value);
			}
			return;
		}
		current = current->next;
	}
	new = ft_malloc(sizeof(t_env));
	if (!new)
		return;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = *env;
	*env = new;
}

int	ft_env_update(t_env **env, char *key, char *value, int overwrite)
{
	t_env	*current;

	if (!env || !*env || !key || !value)
		return (1);
	current = *env;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
		{
			if (overwrite)
			{
				free(current->value);
				current->value = ft_strdup(value);
			}
			return (0);
		}
		current = current->next;
	}
	return (1);
}
