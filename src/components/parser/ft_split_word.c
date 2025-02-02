/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:34:42 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/02 20:58:38 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parser.h"

char **ft_allocat(char *str, char *word, int count, int flag)
{
    char **ret;
    int     i;

    if (count == 0)
        return (NULL);
    ret = ft_malloc(sizeof(char *) * count + flag);
    ret[count] = NULL;
    while (i < count)
    {
        ret[i]
        
    }
}

char **ft_split_word(char *str, char *word)
{
    int     count;
    char    *tmp;
    size_t  len;
    int     flag;
    
    if (!str || !word)
        return (NULL);
    count = 0;
    len = ft_strlen(word);
    tmp = ft_strstr(str, word);
    while (1)
    {
        if (!tmp)
            break ;
        tmp = ft_strstr(tmp + len, word);
        len++;
    }
    if (!tmp + len + 1)
        flag = 1;
    else
        flag = 2;
    return (ft_allocat(str, word, count, flag));
}
