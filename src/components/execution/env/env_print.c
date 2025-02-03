 
#include "../../../../include/execution.h"


void	ft_env_print(t_env *env)
{
	while (env)
	{
		if (env->visible)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
