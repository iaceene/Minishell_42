/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:36:32 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/05 15:36:34 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

int ft_strcmpt(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}
char	*ft_env_search(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmpt(env->key, key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}
