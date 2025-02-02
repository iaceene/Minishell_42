/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:26:56 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/02 11:28:39 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

char *get_value_env(t_env *env_list, const char *key)
{
    t_env *current = env_list;
    
    while (current)
    {
        if (ft_strncmp(current->key, key, ft_strlen(key)) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}
