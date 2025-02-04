 
#include "../../../../include/execution.h"


void	ft_env_delete(t_env **env, char *key)
{
	t_env	*prev;
	t_env	*cur;

	if (!env || !(*env))
		return ;
	prev = *env;
	if (!ft_strncmp(key, prev->key, ft_strlen(prev->key)))
	{
		(*env) = prev->next;
		return ;
		// return (free(prev->key), free(prev->value), free(prev));
	}
	cur = prev->next;
	while (cur)
	{
		if (!ft_strncmp(key, cur->key, ft_strlen(cur->key)))
		{
			prev->next = cur->next;
			// return (free(cur->key), free(cur->value), free(cur));
			return ;
		}
		cur = cur->next;
		prev = prev->next;
	}
}
