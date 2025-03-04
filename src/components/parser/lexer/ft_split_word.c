/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:34:42 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/04 16:35:28 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

static int	ft_count_occurrences(char *str, char *word)
{
	int		count;
	size_t	len;
	char	*tmp;

	count = 0;
	len = ft_strlen(word);
	tmp = str;
	while ((tmp = ft_strstr(tmp, word)))
	{
		count++;
		tmp += len;
	}
	return (count);
}

static char	**ft_allocate_result(int count, int flag)
{
	char	**result;
	int		i;

	result = ft_malloc(sizeof(char *) * (count + flag));
	i = 0;
	while (i < count + flag)
	{
		result[i] = NULL;
		i++;
	}
	return (result);
}

static void	ft_split_into_substrings(char *str, char *word, char **result, int count)
{
	size_t	len;
	char	*tmp;
	int		i;

	len = ft_strlen(word);
	tmp = str;
	i = 0;
	while (i < count)
	{
		char *next = ft_strstr(tmp, word);
		if (!next)
			break ;
		result[i] = ft_malloc(next - tmp + 1);
		ft_strncpy(result[i], tmp, next - tmp);
		result[i][next - tmp] = '\0';
		tmp = next + len;
		i++;
	}
}

static void	ft_handle_last_substring(char *tmp, char **result, int count)
{
	result[count] = ft_strdup(tmp);
}

char	**ft_split_word(char *str, char *word)
{
	int		count;
	int		flag;
	char	**result;

	if (!str || !word)
		return (NULL);
	count = ft_count_occurrences(str, word);
	flag = 2;
	if (ft_strstr(str + ft_strlen(str) - ft_strlen(word), word)
		== str + ft_strlen(str) - ft_strlen(word))
		flag = 1;
	result = ft_allocate_result(count, flag);
	ft_split_into_substrings(str, word, result, count);
	if (flag == 2)
		ft_handle_last_substring(str + ft_strlen(str)
			- ft_strlen(word), result, count);
	return (result);
}