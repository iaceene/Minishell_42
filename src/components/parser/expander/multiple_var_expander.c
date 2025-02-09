/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_var_expander.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 00:26:36 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/09 01:03:11 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

int successive_dollars(char *s)
{
	char *tmp;

	tmp = s;
	while (*tmp)
	{
		if (*(tmp + 1) && *tmp == '$' && *(tmp + 1) == '$')
			return (1);
		tmp++;
	}
	return (0);
}

char *successive_d_handler(char *s)
{
	(void)s;
	printf("there is a successive $$\n");
	return (NULL);
}

int still_dlrs(char *s)
{
	while (*s)
	{
		if (*s == '$')
			return (1);
		s++;
	}
	return (0);
}

char	*none_successive(char *s, t_fake_env *head)
{
	char *final;
	
	final = s;
	while (1)
	{
		final = expand_one_arg(final, head);
		if (!still_dlrs(final))
			break;
	}
	return (final);
}

char *multiple_var_expander(char *s, t_fake_env *head)
{
	if (successive_dollars(s))
		return(successive_d_handler(s));
	else
		return (none_successive(s, head));
	return (NULL);
}