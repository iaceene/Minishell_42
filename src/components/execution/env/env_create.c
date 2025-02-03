 
#include "../../../../include/execution.h"


static char	*ft_get_join_value(char **splited_row)
{
	char	*value;
	int		c;

	value = NULL;
	c = 0;
	while (splited_row[++c])
	{
		if (c == 1)
			value = ft_strjoin(value, ft_strdup(splited_row[c]));
		else
			value = ft_strjoin(value,
					ft_strjoin(ft_strdup("="),
						ft_strdup(splited_row[c])));
	}
	return (value);
}

static int	ft_add_item(t_env **env, char *key, char *value, int visible)
{
	t_env	*new;
	t_env	*last;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (-1);
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->visible = visible;
	last = *env;
	if (!last)
		return (*env = new, 0);
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
	}
	ft_env_delete(&env, "OLDPWD");
	ft_env_add(&env, ft_strdup("OLDPWD"), ft_strdup(""), 0);
	return (env);
}
