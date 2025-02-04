
#include "../../../../include/execution.h"

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