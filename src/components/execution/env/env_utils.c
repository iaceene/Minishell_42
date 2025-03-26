/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:17:32 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/26 17:23:30 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

int	ft_env_update(t_env **env, char *key, char *newval, int append_mod)
{
	t_env	*node;

	node = *env;
	while (node)
	{
		if (!ft_strncmp(node->key, key, ft_strlen(key)))
		{
			if (append_mod)
				node->value = ft_strjoin(node->value, newval);
			else
				node->value = newval;
			node->visible = 1;
			key = NULL;
			return (0);
		}
		node = node->next;
	}
	return (1);
}

int	ft_env_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

int	ft_strcmpt(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char	*ft_env_search(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmpt(env->key, key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

void	ft_print_env(t_env *env)
{
	while (env)
	{
		if (env->visible)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
