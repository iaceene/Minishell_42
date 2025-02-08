/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 02:14:23 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/08 03:35:59 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

t_node *val_node(char *val)
{
    t_node *ret;

    ret = ft_malloc(sizeof(t_node));
    ret->type = WORD;
    ret->value = val;
    return (ret);
}

t_node  *expander(t_node *node, t_fake_env *head, t_cmd **cmd)
{
    char    *value;

    if (!node->next)
        return (add_to_cmd(cmd, new_cmd(NULL)), NULL);
    value = node->next->value;
    while (head)
    {
        if (ft_strncmp(head->key, value, ft_strlen(head->key)) == 0 && 
			ft_strlen(head->key) == ft_strlen(value))
            break;
        head = head->next;
    }
    if (!head)
        add_to_cmd(cmd, new_cmd(NULL));
    else
        add_to_cmd(cmd, new_cmd(val_node(head->value)));
    return (node->next->next);
}