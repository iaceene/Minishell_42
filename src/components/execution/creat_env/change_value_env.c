/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_value_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:30:23 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/02 11:30:57 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../../include/minishell.h"

int change_value_env(t_env **env_list, const char *key, const char *new_value)
{
    t_env *current = *env_list;
    
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            current->value = ft_strdup(new_value);
            return 1;
        }
        current = current->next;
    }
    return 0;
}