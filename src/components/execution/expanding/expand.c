 

#include "../../../../include/execution.h"


static void	handle_quotes(t_expander *exp, char *input)
{
	if (exp->current_quote == 0)
	{
		if (exp->i == 0 || ft_isspace(input[exp->i - 1]))
			exp->is_isolated_quote = 1;
		exp->current_quote = input[exp->i];
	}
	else if (exp->current_quote == input[exp->i])
	{
		if (exp->is_isolated_quote && input[exp->i - 1] == exp->current_quote
			&& (!input[exp->i + 1] || ft_isspace(input[exp->i + 1])))
			ft_lstadd_back(&(exp->head), ft_lstnew(ft_strdup("")));
		exp->current_quote = 0;
		exp->is_isolated_quote = 0;
	}
	else
	{
		exp->buffer = ft_strjoin(exp->buffer, char_to_string(input[exp->i]));
		exp->has_non_whitespace = 1;
	}
}

static void	handle_other_chars(t_expander *exp, char c)
{
	exp->buffer = ft_strjoin(exp->buffer, char_to_string(c));
	if (c != '*' || exp->current_quote != 0)
		exp->has_non_whitespace = 1;
	else
		exp->contains_wildcard = 1;
}

char **expand_input(char *input, t_env *env, int exit_status)
{
	t_expander exp;

	if (!input)
		return (NULL);
	initialize_expander(&exp);
	while (input[++(exp.i)])
	{
		if (ft_isspace(input[exp.i]) && exp.current_quote == 0)
			process_buffer(&exp);
		else if (input[exp.i] == '"' || input[exp.i] == '\'')
			handle_quotes(&exp, input);
		else if (input[exp.i] == '$' && exp.current_quote != '\'')
			expand_dollar_variable(&exp, env, input, exit_status);
		else
			handle_other_chars(&exp, input[exp.i]);
		if (!input[exp.i])
			break;
	}
	if (exp.buffer)
		process_buffer(&exp);
	return (convert_list_to_array(&(exp.head)));
}