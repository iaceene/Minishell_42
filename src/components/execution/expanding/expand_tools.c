 

#include "../../../../include/execution.h"


char	*char_to_string(char c)
{
	char	*str;

	str = ft_malloc(2 * sizeof(char));
	str[0] = c;
	str[1] = '\0';
	return (str);
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

void	initialize_expander(t_expander *exp)
{
	exp->buffer = NULL;
	exp->buff_env = NULL;
	exp->head = NULL;
	exp->i = -1;
	exp->current_quote = 0;
	exp->is_isolated_quote = 0;
	exp->contains_wildcard = 0;
	exp->has_non_whitespace = 0;
}

int	only_wildcards(char *cmd)
{
	if (!cmd)
		return (0);
	while (*cmd && *cmd == '*')
		cmd++;
	return (*cmd == '\0');
}

void	process_buffer(t_expander *exp)
{
	if (exp->buffer)
	{
		if (exp->contains_wildcard && !exp->has_non_whitespace)
			ft_list_cwd(&(exp->head));
		else
		{
			if (only_wildcards(exp->buffer) || !get_matching_files(&(exp->head), exp->buffer))
				ft_lstadd_back(&(exp->head), ft_lstnew(ft_strdup(exp->buffer)));
		}
		exp->buffer = NULL;
		exp->contains_wildcard = 0;
		exp->has_non_whitespace = 0;
		exp->is_isolated_quote = 0;
	}
}
