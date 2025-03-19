/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:51:52 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/31 17:52:01 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (NULL);
	while (s[i])
	{
		if (c == s[i])
		{
			if (s[i + 1])
				return (s + i + 1);
			else
				return (NULL);
		}
		i++;
	}
	return (NULL);
}
