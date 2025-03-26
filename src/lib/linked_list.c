/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:09:46 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/26 02:07:35 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/execution.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = ft_malloc(sizeof(t_list));
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cur_node;

	cur_node = *lst;
	if (cur_node == NULL)
	{
		*lst = new;
		return ;
	}
	while (cur_node->next)
		cur_node = cur_node->next;
	cur_node->next = new;
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*cur_node;

	cur_node = lst;
	if (cur_node == NULL)
		return (NULL);
	while (cur_node->next)
		cur_node = cur_node->next;
	return (cur_node);
}

int	ft_lstsize(t_list *lst)
{
	t_list	*cur_node;
	int		counter;

	cur_node = lst;
	counter = 0;
	while (cur_node)
	{
		counter++;
		cur_node = cur_node->next;
	}
	return (counter);
}

// void	ft_lstclear(t_list **lst)
// {
// 	t_list	*cur_node;
// 	t_list	*nxt_node;

// 	if (!lst)
// 		return ;
// 	cur_node = *lst;
// 	while (cur_node)
// 	{
// 		nxt_node = cur_node->next;
// 		cur_node = nxt_node;
// 	}
// 	*lst = NULL;
// }
