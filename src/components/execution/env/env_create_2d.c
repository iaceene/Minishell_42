 
#include "../../../../include/execution.h"

char	**ft_env_create_2d(t_env *env)
{
	char	**env_2d;
	int		r;

	env_2d = ft_malloc(sizeof(char *) * (ft_env_size(env) + 1));
	if (!env_2d)
	{
		ft_print_err("malloc failed\n");
		return (NULL);
	}
	r = 0;
	while (env)
	{
		env_2d[r++] = ft_strjoin(ft_strdup(env->key),
				ft_strjoin(ft_strdup("="), ft_strdup(env->value)));
		env = env->next;
	}
	env_2d[r] = NULL;
	return (env_2d);
}
