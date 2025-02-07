#include "../../../include/minishell.h"




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
	t_cmd	*last;
	
	if (!head)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	else
	{
		last = *head;
		while (last && last->next)
			last = last->next;
		last->next = new;
	}
}

int no_need(TokenType tp)
{
	return (tp == OPEN_PAR || tp == CLOSE_PAR || tp == SIN_QUOTE || tp == DOB_QUOTE);
}

void print_command(t_cmd *cmd);

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
	// print_command(cmd);
	return (cmd);
}

void print_command(t_cmd *cmd)
{
	int i = 0;
	while (cmd)
	{
		printf("====\ncommand %s\nN : %d\nType %d\n", cmd->value, i, cmd->type);
		i++;
		cmd = cmd->next;
	}
}