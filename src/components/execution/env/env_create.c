/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:20:30 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/02 20:40:31 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static char *ft_strtok_r(char *str, const char *delim, char **saveptr)
{
    char *token;

    if (str == NULL)
        str = *saveptr;
    if (str == NULL)
        return NULL;
    str += strspn(str, delim);
    if (*str == '\0')
        return NULL;
    token = str;
    str = strpbrk(token, delim);
    if (str == NULL)
        *saveptr = NULL;
    else
        (*str = '\0', *saveptr = str + 1);
    return token;
}

t_env	*ft_env_create(char **envp)
{
	t_env	*env_list;
	t_env	*new_node;
	char	*key;
	char	*value;
	char	*saveptr;
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
		key = ft_strdup(ft_strtok_r(envp[i], "=", &saveptr));
		value = ft_strdup(saveptr);
		if (!key || !value)
		{
			free(key);
			free(value);
			free(new_node);
			return (NULL);
		}
		new_node->key = key;
		new_node->value = value;
		new_node->next = env_list;
		env_list = new_node;
		i++;
	}
	return (env_list);
}
