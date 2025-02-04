 

#include "../../../../include/execution.h"


static int is_alphanumeric_or_underscore(char c)
{
	return (('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z')
		|| ('0' <= c && c <= '9')
		|| (c == '_'));
}

static int is_digit(char c)
{
	return ('0' <= c && c <= '9');
}

static void process_special_case(t_expander *exp, char *input, int exit_status, char *env_value)
{
	if (input[exp->i] == '*' && input[exp->i - 1] == '$')
		(exp->i)++;
	else if (input[exp->i] == '*')
		exp->contains_wildcard = 1;
	if (ft_strlen(exp->buff_env) == 1)
	{
		if (input[exp->i] == '?')
		{
			exp->buffer = ft_strjoin(exp->buffer, ft_itoa(exit_status));
			(exp->i)++;
		}
		else if ((input[exp->i] != '\'' && input[exp->i] != '"' && exp->current_quote == 0)
			|| exp->current_quote != 0)
		{
			exp->buffer = ft_strjoin(exp->buffer, char_to_string('$'));
			exp->has_non_whitespace = 1;
		}
	}
	(exp->i)--;
	free(exp->buff_env);
	free(env_value);
	exp->buff_env = NULL;
}

static void append_env_value_to_buffer(t_expander *exp, char *env_value)
{
	int i = 0;
	while (env_value[i])
	{
		if (ft_isspace(env_value[i]))
			process_buffer(exp);
		else
			exp->buffer = ft_strjoin(exp->buffer, char_to_string(env_value[i]));
		i++;
	}
	if (only_wildcards(env_value))
		exp->contains_wildcard = 1;
	else
		exp->has_non_whitespace = 1;
}

void expand_dollar_variable(t_expander *exp, t_env *env, char *input, int exit_status)
{
	char *env_value;

	exp->buff_env = char_to_string(input[(exp->i)++]);
	while (input[exp->i] && is_alphanumeric_or_underscore(input[exp->i]))
	{
		if (is_digit(input[exp->i]) && input[exp->i - 1] == '$')
		{
			free(exp->buff_env);
			exp->buff_env = NULL;
			break;
		}
		exp->buff_env = ft_strjoin(exp->buff_env, char_to_string(input[(exp->i)++]));
	}
	if (!exp->buff_env)
		return;
	env_value = ft_env_search(env, exp->buff_env + 1);
	if (!env_value && exp->current_quote)
		exp->buffer = ft_strjoin(exp->buffer, ft_strdup(""));
	else if (env_value && exp->current_quote == 0)
		append_env_value_to_buffer(exp, env_value);
	else if (env_value && exp->current_quote != 0)
		exp->buffer = ft_strjoin(exp->buffer, ft_strdup(env_value));
	process_special_case(exp, input, exit_status, env_value);
}