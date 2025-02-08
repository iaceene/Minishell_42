/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 22:07:36 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/31 18:36:37 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/execution.h"

t_fake_env *fake_env(char *key, char *value)
{
	t_fake_env *n;

	n = ft_malloc(sizeof(t_fake_env));
	n->key = key;
	n->value = value;
	n->next = NULL;
	return (n);
}

void add_fake_env(t_fake_env **head, t_fake_env *new)
{
	t_fake_env *lst;

	lst = *head;
	if (!*head)
	{
		*head = new;
		return ;
	}
	else
	{
		while (lst &&  lst->next)
			lst = lst->next;
		lst->next = new;
	}
}

t_fake_env *fake_env_creator()
{
	int i;
	t_fake_env *head;

	i = 0;
	head = NULL;
	while (i < 7)
	{
		if (i == 0)
			add_fake_env(&head, fake_env(ft_strdup("n"), ft_strdup("1234")));
		if (i == 1)
			add_fake_env(&head, fake_env(ft_strdup("abc"), ft_strdup("abcdefjhg")));
		if (i == 2)
			add_fake_env(&head, fake_env(ft_strdup("name"), ft_strdup("yassine")));
		if (i == 3)
			add_fake_env(&head, fake_env(ft_strdup("last name"), ft_strdup("ajagro")));
		if (i == 4)
			add_fake_env(&head, fake_env(ft_strdup("school"), ft_strdup("1337 khouribga")));
		if (i == 5)
			add_fake_env(&head, fake_env(ft_strdup("device"), ft_strdup("imac")));
		if (i == 6)
			add_fake_env(&head, fake_env(ft_strdup("brand"), ft_strdup("apple")));
		i++;
	}
	return (head);
}

int parser(t_data *data)
{
	t_node *tock_data;
	t_fake_env *head;

	head = fake_env_creator();
	tock_data = lexer_init(data->prompt);
	if (!tock_data)
		return (0);
	if (syntax_checker(tock_data) == -1)
		return (0);
	else
		data->head = data_maker(tock_data, head);
	if (!data->head)
		return (0);
	return (1);
}
