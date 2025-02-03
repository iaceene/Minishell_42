 
#include "../../../../include/execution.h"


int	ft_env_add(t_env **env, char *key, char *value, int visible)
{
	t_env	*new;
	t_env	*last;

	new = ft_malloc(sizeof(t_env));
	if (new == NULL)
		return (ft_print_err("malloc failed\n"), -1);
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->visible = visible;
	last = *env;
	if (!last)
		return (*env = new, 0);
	if (ft_strncmp(new->key, last->key, ft_strlen(last->key)) < 0)
		return (new->next = *env, *env = new, 0);
	while (last && last->next)
	{
		if (ft_strncmp(new->key, last->next->key, ft_strlen(last->next->key)) < 0)
			return (new->next = last->next, last->next = new, 0);
		last = last->next;
	}
	last->next = new;
	return (0);
}
