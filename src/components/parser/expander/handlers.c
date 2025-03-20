/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 23:29:48 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/20 03:11:04 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

void	handle_single_quote(char **input, t_expand **head, t_state *state)
{
	char		*start;
	char		*tmp;
	t_expand	*node;

	*state = IN_SQUOTE;
	(*input)++;
	start = *input;
	while (**input && **input != '\'')
		(*input)++;
	tmp = ft_substr(start, 0, *input - start);
	set_space_zero(tmp);
	node = new_expand(*state, tmp);
	add_expand(head, node);
	if (**input)
		(*input)++;
	*state = NORMAL;
}

void	handle_double_quote(char **input, t_expand **head, t_state *state)
{
	char		*start;
	char		*tmp;
	t_expand	*node;

	*state = IN_DQUOTE;
	(*input)++;
	start = *input;
	while (**input && **input != '"')
		(*input)++;
	tmp = ft_substr(start, 0, *input - start);
	set_space_zero(tmp);
	node = new_expand(*state, tmp);
	add_expand(head, node);
	if (**input)
		(*input)++;
	*state = NORMAL;
}

void	handle_normal_text(char **input, t_expand **head, t_state state)
{
	char		*start;
	t_expand	*node;

	start = *input;
	while (**input && **input != '\'' && **input != '"')
		(*input)++;
	node = new_expand(state, ft_substr(start, 0, *input - start));
	add_expand(head, node);
}

void	set_space_zero(char *tmp)
{
	int	i;

	i = 0;
	if (!tmp)
		return ;
	while (tmp[i])
	{
		if (tmp[i] == ' ')
			tmp[i] = -1;
		i++;
	}
}

void	set_space_zero_qoats(char *tmp)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	if (!tmp)
		return ;
	while (tmp[i])
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
			in_quotes = !in_quotes;
		if (tmp[i] == ' ' && in_quotes)
			tmp[i] = -1;
		i++;
	}
}

void	set_zero_space(char **s)
{
	int i;
	int	j;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] == -1)
				s[i][j] = ' ';
			j++;
		}
		i++;
	}
}

void replace_character(char *s, int re)
{
    int i;
	int j;

	i = 0;
	j = 0;
    while (s[i])
    {
        if (s[i] != re)
            s[j++] = s[i];
        i++;
    }
    s[j] = '\0';
}

void	set_empty_str(char **s)
{
	int		i;
	int		j;
	bool	f;

	if (!s)
		return ;
	f = (*s && ft_strlen(*s) > 1);
	i = -1;
	while (s[++i])
	{
		j = -1;
		while (s[i][++j])
			if (s[i][j] == -2 && !f)
				s[i][j] = '\0';
		if (f)
			replace_character(s[i], -2);
	}
}
