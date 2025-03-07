/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:43:44 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/07 21:15:31 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

typedef struct s_buffer
{
	char	*val;
	struct s_buffer *next;
}t_buffer;


t_buffer *new_buff(char *val)
{
	t_buffer	*ret;

	ret = ft_malloc(sizeof(t_buffer));
	ret->next = NULL;
	ret->val = val;
	return (ret);
}

void	add_buff(t_buffer **head, t_buffer *new)
{
	t_buffer *tmp;

	tmp = *head;
	if (!head || !new)
		return;
	if (!*head)
		*head = new;
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	*join_buffer(t_buffer *head)
{
	char	*joined;

	joined = NULL;
	while (head)
	{
		joined = ft_strjoin(joined, head->val);
		head = head->next;
	}
	return (joined);
}

char	*herdoc(t_env *env, char *exit)
{
	(void)env;
	char		*prom;
	t_buffer	*head;
	
	head = NULL;
	while (1)
	{
		prom = readline("> ");
		if (prom && !ft_strncmp(prom, exit, ft_strlen(prom)))
			break ;
		add_buff(&head, new_buff(prom));
	}
	if (!head)
		return (ft_strdup(""));
	return (join_buffer(head));
}