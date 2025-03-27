/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:18:10 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/27 20:56:17 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

int	find_it(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

int	check_qoats(char *val)
{
	int	single;
	int	doubl;

	single = 0;
	doubl = 0;
	while (*val)
	{
		if (*val == '\'' && doubl == 0)
			single = !single;
		else if (*val == '"' && single == 0)
			doubl = !doubl;
		val++;
	}
	return (single || doubl);
}

int	check_herdoc(t_node *data)
{
	while (data)
	{
		if (data->type == HERDOC)
		{
			if (!data->next)
				return (1);
			if (data->next->type != COMMAND)
				return (0);
		}
		data = data->next;
	}
	return (0);
}

int	others_checker(t_node *data)
{
	while (data)
	{
		if (data->type == COMMAND)
			if (check_qoats(data->value))
				return (0);
		if (data->type == OPEN_PAR || data->type == CLOSE_PAR)
			return (0);
		data = data->next;
	}
	if (check_herdoc(data))
		return (0);
	return (1);
}

int	calculate_word_length(char *s, int *in_quotes, char *quote_char)
{
	int	len;

	len = 0;
	while (*s && (*in_quotes || !operator(*s)))
	{
		if ((*s == '\'' || *s == '"') && !(*in_quotes))
		{
			*in_quotes = 1;
			*quote_char = *s;
		}
		else if (*s == *quote_char && *in_quotes)
		{
			*in_quotes = 0;
			*quote_char = 0;
		}
		s++;
		len++;
	}
	return (len);
}
