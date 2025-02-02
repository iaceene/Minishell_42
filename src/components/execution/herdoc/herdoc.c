/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:58:31 by behave_shel       #+#    #+#             */
/*   Updated: 2025/02/02 19:41:48 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static int is_valid_identifier_char(char c)
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9') || (c == '_'));
}

static int is_numeric_char(char c)
{
	return ('0' <= c && c <= '9');
}

static void expand_dollar(char *input, t_expand_herdoc *exp)
{
	char *env_value;

	exp->buffer_env = ft_char_to_str(input[(exp->i)++]);
	while (input[exp->i] && is_valid_identifier_char(input[exp->i]))
	{
		if (is_numeric_char(input[exp->i]) && input[exp->i - 1] == '$')
		{
			free(exp->buffer_env);
			exp->buffer_env = NULL;
			return;
		}
		exp->buffer_env = ft_strjoin2(exp->buffer_env, ft_char_to_str(input[(exp->i)++]));
	}
	if (!exp->buffer_env)
		return;
	env_value = ft_env_search(exp->env, exp->buffer_env + 1);
	exp->buffer_exp = ft_strjoin2(exp->buffer_exp, env_value ? env_value : "");
	free(exp->buffer_env);
}

char *expand_heredoc_input(char *input, t_env *env, int exit_code)
{
	t_expand_herdoc exp;
	exp.buffer_env = NULL;
	exp.buffer_exp = NULL;
	exp.i = 0;
	exp.exit_status = exit_code;
	exp.env = env;
	while (input[exp.i])
	{
		if (input[exp.i] == '$')
			expand_dollar(input, &exp);
		else
			exp.buffer_exp = ft_strjoin2(exp.buffer_exp, ft_char_to_str(input[exp.i]));
		(exp.i)++;
	}
	return (exp.buffer_exp);
}

void process_here_doc(char *delimiter, int *pipe_fd, t_env *env, int exit_code)
{
	char *input;
	char *expanded;

	if (pipe(pipe_fd) == -1)
		error_and_exit("Failed to create pipe for heredoc\n", 1);
	while (1)
	{
		write(1, "heredoc> ", 9);
		input = readline(0);
		if (!input)
		{
			write(1, "\n", 1);
			break;
		}
		if (ft_strncmp(input, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(input);
			break;
		}
		expanded = expand_heredoc_input(input, env, exit_code);
		free(input);
		write(pipe_fd[1], expanded, ft_strlen(expanded));
		write(pipe_fd[1], "\n", 1);
		free(expanded);
	}
	close(pipe_fd[1]);
}
