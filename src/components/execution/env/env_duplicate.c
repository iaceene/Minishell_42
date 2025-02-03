 
#include "../../../../include/execution.h"


t_env	*ft_env_duplicate(t_env *env)
{
	t_env	*env_dup;

	env_dup = NULL;
	while (env)
	{
		ft_env_add(&env_dup, ft_strdup(env->key),
			ft_strdup(env->value), env->visible);
		env = env->next;
	}
	return (env_dup);
}
