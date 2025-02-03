 
#include "../../../../include/execution.h"


static char	*ft_get_join_value(char **splited_row)
{
    char	*value;
    char	*tmp;
    int		c;

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


static int	ft_add_item(t_env **env, char *key, char *value, int visible)
{
	// printf("Adding key: %s, value: %s\n", key, value);
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
