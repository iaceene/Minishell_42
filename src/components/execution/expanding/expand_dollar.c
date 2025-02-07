

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

static void process_special_case(t_expander *arg, char *input, int exit_status, char *env_value)
{
	if (input[arg->i] == '*' && input[arg->i - 1] == '$')
		(arg->i)++;
	else if (input[arg->i] == '*')
		arg->contains_wildcard = 1;
	if (ft_strlen(arg->buff_env) == 1)
	{
		if (input[arg->i] == '?')
		{
			arg->buffer = ft_strjoin(arg->buffer, ft_itoa(exit_status));
			(arg->i)++;
		}
		else if ((input[arg->i] != '\'' && input[arg->i] != '"' && arg->current_quote == 0)
			|| arg->current_quote != 0)
		{
			arg->buffer = ft_strjoin(arg->buffer, char_to_string('$'));
			arg->has_non_whitespace = 1;
		}
	}
	(arg->i)--;
	free(arg->buff_env);
	free(env_value);
	arg->buff_env = NULL;
}

static void append_env_value_to_buffer(t_expander *arg, char *env_value)
{
	int i = 0;
	while (env_value[i])
	{
		if (ft_isspace(env_value[i]))
			process_buffer(arg);
		else
			arg->buffer = ft_strjoin(arg->buffer, char_to_string(env_value[i]));
		i++;
	}
	if (only_wildcards(env_value))
		arg->contains_wildcard = 1;
	else
		arg->has_non_whitespace = 1;
}

void expand_dollar_variable(t_expander *arg, t_env *env, char *input, int exit_status)
{
	char *env_value;

	arg->buff_env = char_to_string(input[(arg->i)++]);
	while (input[arg->i] && is_alphanumeric_or_underscore(input[arg->i]))
	{
		if (is_digit(input[arg->i]) && input[arg->i - 1] == '$')
		{
			free(arg->buff_env);
			arg->buff_env = NULL;
			break;
		}
		arg->buff_env = ft_strjoin(arg->buff_env, char_to_string(input[(arg->i)++]));
	}
	if (!arg->buff_env)
		return;
	// printf("buff_env: %s\n", arg->buff_env);
	env_value = ft_env_search(env, arg->buff_env + 1);
	// printf("env_value: %s\n", env_value);
	if (!env_value && arg->current_quote)
		arg->buffer = ft_strjoin(arg->buffer, ft_strdup(""));
	else if (env_value && arg->current_quote == 0)
		append_env_value_to_buffer(arg, env_value);
	else if (env_value && arg->current_quote != 0)
		arg->buffer = ft_strjoin(arg->buffer, ft_strdup(env_value));
	process_special_case(arg, input, exit_status, env_value);
}