 

#include "../../../../include/execution.h"


char	*char_to_string(char c)
{
	char	str[2];

	// str = ft_malloc(2 * sizeof(char));
	str[0] = c;
	str[1] = '\0';
	return (ft_strdup(str));
}

char	**convert_list_to_array(t_list **head)
{
	char	**array;
	int		size;
	int		i;
	t_list	*current;

	size = ft_lstsize(*head);
	array = (char **)ft_malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	i = 0;
	current = *head;
	while (current)
	{
		array[i++] = ft_strdup(current->content);
		current = current->next;
	}
	array[i] = NULL;
	// ft_lstclear(head);
	return (array);
}

void	initialize_expander(t_expander *arg)
{
	arg->buffer = NULL;
	arg->buff_env = NULL;
	arg->head = NULL;
	arg->i = -1;
	arg->current_quote = 0;
	arg->is_isolated_quote = 0;
	arg->contains_wildcard = 0;
	arg->has_non_whitespace = 0;
}

int	only_wildcards(char *cmd)
{
	if (!cmd)
		return (0);
	while (*cmd && *cmd == '*')
		cmd++;
	return (*cmd == '\0');
}

void	process_buffer(t_expander *arg)
{
	if (arg->buffer)
	{
		if (arg->contains_wildcard && !arg->has_non_whitespace)
			ft_list_cwd(&(arg->head));
		else
		{
			if (only_wildcards(arg->buffer) || !get_matching_files(&(arg->head), arg->buffer))
				ft_lstadd_back(&(arg->head), ft_lstnew(ft_strdup(arg->buffer)));
		}
		free(arg->buffer);
		arg->buffer = NULL;
		arg->contains_wildcard = 0;
		arg->has_non_whitespace = 0;
		arg->is_isolated_quote = 0;
	}
}
