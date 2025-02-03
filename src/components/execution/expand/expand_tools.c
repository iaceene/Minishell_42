/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:32:15 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/03 19:48:51 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 

#include "../../../../include/minishell.h"

char	*ft_char_to_str(char c)
{
	char	str[2];

	str[0] = c;
	str[1] = 0;
	return (ft_strdup(str));
}

char	**ft_lst_to_2d_char(t_list **head)
{
	printf("lst_to_2d_char\n");
	char	**char_2d;
	int		r;
	t_list	*cur;

	char_2d = ft_malloc(sizeof(char *) * (ft_lstsize(*head) + 1));
	r = 0;
	cur = *head;
	// printf("c %c\n", cur->content);
	while (cur)
	{
		printf(" 1\n");
		char_2d[r] = ft_strdup(cur->content);
		cur = cur->next;
		r++;
	}
	char_2d[r] = NULL;
	ft_lstclear(head);
	return (char_2d);
}

void	ft_exp_init(t_expand *exp)
{
	exp->buff_exp = NULL;
	exp->buff_env = NULL;
	exp->head = NULL;
	exp->i = -1;
	exp->quote = 0;
	exp->noting_before_quote = 0;
	exp->found_star = 0;
	exp->found_another_char = 0;
}

int	ft_only_star(char *cmd)
{
	if (!cmd)
		return (0);
	while (*cmd && *cmd == '*')
		cmd++;
	return (*cmd == 0);
}

void	ft_expand_cut(t_expand *exp)
{
	printf("cut\n");
	if (exp->buff_exp)
	{
		if (exp->found_star && !exp->found_another_char)
			ft_list_cwd(&(exp->head));
		else
		{
			if (ft_only_star(exp->buff_exp) || \
			!ft_get_matching(&(exp->head), exp->buff_exp))
				ft_lstadd_back(&(exp->head), \
				ft_lstnew(ft_strdup(exp->buff_exp)));
		}
		free(exp->buff_exp);
		exp->buff_exp = NULL;
		exp->found_star = 0;
		exp->found_another_char = 0;
		exp->noting_before_quote = 0;
	}
}
