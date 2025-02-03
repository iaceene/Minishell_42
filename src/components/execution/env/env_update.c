 
#include "../../../../include/execution.h"


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
			{
				free(node->value);
				node->value = newval;
			}
			node->visible = 1;
			free(key);
			key = NULL;
			return (0);
		}
		node = node->next;
	}
	return (1);
}
