 
#include "../../../../include/execution.h"


char	*ft_env_search(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}
