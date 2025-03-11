char *handle_quotes(char *input)
{
	t_expand	*head;
	t_expand	*node;
	State		state;
	char		*start;

	head = NULL;
	state = NORMAL;
	while (*input)
	{
		if (*input == '\'' && state == NORMAL) // Enter single-quoted mode
		{
			state = IN_SQUOTE;
			input++;
			start = input;
			while (*input && *input != '\'') // Collect inside single quotes
				input++;
			node = new_expand(state, ft_substr(start, 0, input - start));
			add_expand(&head, node);
			if (*input) // Skip closing quote
				input++;
			state = NORMAL;
		}
		else if (*input == '"' && state == NORMAL) // Enter double-quoted mode
		{
			state = IN_DQUOTE;
			input++;
			start = input;
			while (*input && *input != '"') // Collect inside double quotes
				input++;
			node = new_expand(state, ft_substr(start, 0, input - start));
			add_expand(&head, node);
			if (*input) // Skip closing quote
				input++;
			state = NORMAL;
		}
		else // Normal text (outside quotes)
		{
			start = input;
			while (*input && *input != '\'' && *input != '"')
				input++;
			node = new_expand(state, ft_substr(start, 0, input - start));
			add_expand(&head, node);
		}
	}
	return (expand_and_join(head));
}