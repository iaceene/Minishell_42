
#include "../../../../include/execution.h"

t_env *ft_env_create_default(void)
{
	t_env *head = NULL;

	ft_env_add(&head, "PWD", "/", 1);
	// ft_env_add(&head, "OLDPWD", "/home/iezzam/kaneki", 1);
	ft_env_add(&head, "SHLVL", "1", 1);
	ft_env_add(&head, "_", "/usr/bin/env", 1);
	ft_env_add(&head, "PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 1);

	return head;
}

char **ft_env_create_2d(t_env *env)
{
	int count;
	int i;
	t_env *temp;

	count = 0;
	temp = env;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	char **envp = ft_malloc((count + 1) * sizeof(char *));
	temp = env;
	i = 0;
	while (i < count)
	{
		int key_len = ft_strlen(temp->key);
		int value_len = ft_strlen(temp->value);
		int len = key_len + value_len + 2;

		envp[i] = ft_malloc(len * sizeof(char));
		ft_memcpy(envp[i], temp->key, key_len);
		envp[i][key_len] = '=';
		ft_memcpy(envp[i] + key_len + 1, temp->value, value_len);
		envp[i][len - 1] = '\0';
		temp = temp->next;
		i++;
	}
	envp[count] = NULL;
	return envp;
}

static char *ft_get_join_value(char **splited_row)
{
	char *value;
	char *tmp;
	int c;

	value = NULL;
	c = 0;
	while (splited_row[++c])
	{
		if (c == 1)
			value = ft_strdup(splited_row[c]);
		else
		{
			tmp = value;
			value = ft_strjoin(value, "=");
			// free(tmp);
			tmp = value;
			value = ft_strjoin(value, splited_row[c]);
			// free(tmp);
		}
	}
	// printf("Generated value: %s\n", value); // 🔴 DEBUG
	return (value);
}

static int ft_add_item(t_env **env, char *key, char *value, int visible)
{
	// printf("Adding key: %s, value: %s\n", key, value);
	t_env *new;
	t_env *last;

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

t_env *ft_env_create(char **ev)
{
	t_env *env;
	char **splited_row;
	int r;
	char *key;
	char *value;

	t_env *head;

	head = NULL;
	if (!ev || !*ev)
		return ft_env_create_default();

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

		// int i = 0;
		// while (splited_row[i])
		// 	free(splited_row[i++]);
		// free(splited_row);
	}
	ft_env_delete(&env, "OLDPWD");
	ft_env_add(&env, ft_strdup("OLDPWD"), ft_strdup(""), 0);
	return (env);
}
