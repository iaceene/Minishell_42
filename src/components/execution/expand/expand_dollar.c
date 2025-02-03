/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:32:39 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/03 15:16:09 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../../include/minishell.h"

static int	ft_is_valid_char(char c)
{
	return (('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z')
		|| ('0' <= c && c <= '9')
		|| (c == '_'));
}

static int	ft_is_numeric(char c)
{
	return ('0' <= c && c <= '9');
}

static void	ft_help(t_expand *exp, char *cmd, int exit_status, char *env_var)
{
	if (cmd[exp->i] == '*' && cmd[exp->i - 1] == '$')
		(exp->i)++;
	else if (cmd[exp->i] == '*')
		exp->found_star = 1;
	if (ft_strlen(exp->buff_env) == 1)
	{
		if (cmd[exp->i] == '?')
		{
			exp->buff_exp = ft_strjoin(exp->buff_exp, ft_itoa(exit_status));
			(exp->i)++;
		}
		else if ((cmd[exp->i] != '\'' && cmd[exp->i] != '"' && exp->quote == 0)
			|| exp->quote != 0)
		{
			exp->buff_exp = ft_strjoin(exp->buff_exp, ft_char_to_str('$'));
			exp->found_another_char = 1;
		}
	}
	(exp->i)--;
	free(exp->buff_env);
	free(env_var);
	exp->buff_env = NULL;
}

static void	ft_add_to_expand_buffer(t_expand *exp, char *env_var)
{
	int		i;

	i = 0;
	while (env_var[i])
	{
		if (ft_isspace(env_var[i]))
			ft_expand_cut(exp);
		else
			exp->buff_exp = ft_strjoin(exp->buff_exp,
					ft_char_to_str(env_var[i]));
		i++;
	}
	if (ft_only_star(env_var))
		exp->found_star = 1;
	else
		exp->found_another_char = 1;
}

void	ft_expand_dollar(t_expand *exp, t_env *env, char *cmd, int exit_status)
{
	char	*env_var;

	exp->buff_env = ft_char_to_str(cmd[(exp->i)++]);
	while (cmd[exp->i] && ft_is_valid_char(cmd[exp->i]))
	{
		if (ft_is_numeric(cmd[exp->i]) && cmd[exp->i - 1] == '$')
		{
			free(exp->buff_env);
			exp->buff_env = NULL;
			break ;
		}
		exp->buff_env = ft_strjoin(exp->buff_env,
				ft_char_to_str(cmd[(exp->i)++]));
	}
	if (!exp->buff_env)
		return ;
	env_var = ft_env_search(env, exp->buff_env + 1);
	if (!env_var && exp->quote)
		exp->buff_exp = ft_strjoin(exp->buff_exp, ft_strdup(""));
	else if (env_var && exp->quote == 0)
		ft_add_to_expand_buffer(exp, env_var);
	else if (env_var && exp->quote != 0)
		exp->buff_exp = ft_strjoin(exp->buff_exp, ft_strdup(env_var));
	ft_help(exp, cmd, exit_status, env_var);
}
