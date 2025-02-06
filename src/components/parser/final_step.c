#include "../../../include/parser.h"




t_cmd	*new_cmd(t_node *node)
{
	t_cmd *ret;

	ret = ft_malloc(sizeof(t_cmd));
	ret->type = node->type;
	ret->value = node->value;
	ret->next = NULL;
	return (ret);
}

void add_to_cmd(t_cmd **head, t_cmd *new)
{
	t_cmd *lst;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	else
	{
		lst = *head;
		while (lst && lst->next)
			lst = lst->next;
		lst = new;
	}
}

int no_need(TokenType tp)
{
	return (tp == OPEN_PAR || tp == CLOSE_PAR || tp == SIN_QUOTE || tp == DOB_QUOTE);
}

t_cmd	*data_maker(t_node *head)
{
	t_cmd *cmd;

	if (!head)
		return (NULL);
	cmd = NULL;
	while (head)
	{
		if (!no_need(head->type))
			add_to_cmd(&cmd, new_cmd(head));
		head = head->next;
	}
	return (cmd);
}