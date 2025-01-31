/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:19:00 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/31 09:19:00 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


static void	ft_free(char **ptr, int k)
{
	int	i;

	if (!ptr)
		return;
	i = 0;
	while (i < k)
		free(ptr[i++]);
	free(ptr);
}

static int is_operator(const char *s)
{
	if (!s)
		return (0);
	if (!ft_strncmp(s, "&&", 2) || !ft_strncmp(s, "||", 2) ||
		!ft_strncmp(s, ">>", 2) || !ft_strncmp(s, "<<", 2))
		return (2);
	if (*s == '|' || *s == '>' || *s == '<')
		return (1);
	return (0);
}

size_t get_token_length(const char *s)
{
	size_t len = 0;
	int op_len;

	if (!s || !*s)
		return (0);
	op_len = is_operator(s);
	if (op_len)
		return (op_len);
	if (*s == '"' || *s == '\'')
	{
		char quote = *s++;
		while (s[len] && s[len] != quote)
			len++;
		if (s[len] == quote)
			return (len + 2);
		write(2, "Syntax error: unmatched quote\n", 30);
		return (0);
	}
	while (s[len] && !is_operator(s + len) && !ft_isspace(s[len]))
		len++;
	return (len);
}

int ft_check_syntax(const char *s)
{
    size_t token_len;
    int last_was_operator = 0;
    int first_token = 1;

    while (*s)
    {
        while (*s && ft_isspace(*s))
            s++;
        if (!*s)
            break;

        token_len = get_token_length(s);
        if (token_len == 0)
            return (1);

        if (is_operator(s))
        {
            if (last_was_operator)
            {
                dprintf(2, "bash: syntax error near unexpected token `%.*s'\n", (int)token_len, s);
                return (1);
            }
            if (first_token)
            {
                dprintf(2, "bash: syntax error near unexpected token `%.*s'\n", (int)token_len, s);
                return (1);
            }
            if (!ft_strncmp(s, "<<<", 3))
            {
                s += 3;
                while (*s && ft_isspace(*s))
                    s++;
                if (!*s || is_operator(s))
                {
                    dprintf(2, "bash: syntax error near unexpected token `<'\n");
                    return (1);
                }
                last_was_operator = 0;
                continue;
            }
            last_was_operator = 1;
        }
        else
        {
            last_was_operator = 0;
        }

        first_token = 0;
        s += token_len;
    }

    if (last_was_operator)
    {
        dprintf(2, "bash: syntax error near unexpected token `newline'\n");
        return (1);
    }
    return (0);
}

size_t ft_count_tokens(const char *s)
{
	size_t count = 0;
	size_t len;

	while (s && *s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (!*s)
			break;
		len = get_token_length(s);
		count++;
		s += len;
	}
	return count;
}

char **ft_split_shell(const char *s)
{
	char **result;
	size_t i = 0, len;
	size_t token_count;

	if (!s || ft_check_syntax(s))
		return (NULL);
	token_count = ft_count_tokens(s);
	result = malloc((token_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (!*s)
			break;
		len = get_token_length(s);
		result[i] = ft_substr(s, 0, len);
		if (!result[i])
		{
			ft_free(result, i);
			return (NULL);
		}
		i++;
		s += len;
	}
	result[i] = NULL;
	return result;
}
