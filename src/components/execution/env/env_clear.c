 

#include "../../../../include/execution.h"


void	ft_env_clear(t_env **env)
{
	t_env	*cur_node;
	t_env	*nxt_node;

	if (!env)
		return ;
	cur_node = *env;
	while (cur_node)
	{
		nxt_node = cur_node->next;
		free(cur_node->key);
		free(cur_node->value);
		free(cur_node);
		cur_node = nxt_node;
	}
	*env = NULL;
}
