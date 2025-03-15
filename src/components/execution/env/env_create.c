/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 06:29:41 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/15 06:35:51 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

t_env	*ft_env_create_default(void)
{
	t_env	*head;

	head = NULL;
	ft_env_add(&head, "PWD", "/", 1);
	ft_env_add(&head, "SHLVL", "1", 1);
	ft_env_add(&head, "_", "/usr/bin/env", 1);
	ft_env_add(&head, "PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 1);
	return (head);
}

static char	*ft_get_join_value(char **splited_row)
{
	char	*value;
	int		c;

	value = NULL;
	c = 0;
	while (splited_row[++c])
	{
		if (c == 1)
			value = ft_strdup(splited_row[c]);
		else
		{
			value = ft_strjoin(value, "=");
			value = ft_strjoin(value, splited_row[c]);
		}
	}
	return (value);
}

static int	ft_add_item(t_env **env, char *key, char *value, int visible)
{
	t_env	*new;
	t_env	*last;

	new = ft_malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->visible = visible;
	if (!*env)
	{
		*env = new;
		return (0);
	}
	last = *env;
	while (last->next)
		last = last->next;
	last->next = new;
	return (0);
}

t_env	*ft_env_create(char **ev)
{
	t_env	*env;
	char	**splited_row;
	int		r;
	char	*key;
	char	*value;

	if (!ev || !*ev)
		return (ft_env_create_default());
	r = -1;
	env = NULL;
	while (ev[++r])
	{
		splited_row = ft_split(ev[r], EQUAL);
		if (!splited_row)
			return (NULL);
		key = ft_strdup(splited_row[0]);
		value = ft_get_join_value(splited_row);
		ft_add_item(&env, key, value, 1);
	}
	ft_env_delete(&env, "OLDPWD");
	ft_env_add(&env, ft_strdup("OLDPWD"), ft_strdup(""), 0);
	return (env);
}
