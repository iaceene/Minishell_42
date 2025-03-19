/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:48:34 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/31 18:42:28 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_terminal(void)
{
	write(1, "\033[H\033[J", 6);
}

static void	ft_init(t_tool *tool, char **env, t_data *data)
{
	tool->env = ft_env_create(env);
	data->final_env = tool->env;
	tool->env->a_ven = ft_env_create_2d(tool->env);
	data->exe_state = 0;
}

void	printing(char **v)
{
	int	i;

	i = 0;
	while (v[i])
	{
		if (i == 0)
			printf("CMD [%s]\n", v[i]);
		else
			printf("ARG [%s]\n", v[i]);
		i++;
	}
}

void	print_final_data(t_cmd *head, int *exit)
{
	fprintf(stderr, "exit_status---------------%d\n", *exit);
	while (head)
	{
		if (head->type == COMMAND)
			printing(head->cmd);
		else if (head->type == IN_FILE)
			printf("infile [%s]\n", head->value);
		else if (head->type == OUT_FILE)
			printf("outfile [%s]\n", head->value);
		else if (head->type == APPEND)
			printf("append [%s]\n", head->value);
		else if (head->type == HERDOC)
			printf("herdoc val [%s]\n", head->value);
		else if (head->value)
			printf("%s\n", head->value);
		head = head->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_tool	tool;

	clear_terminal();
	data.env = env;
	signal(SIGINT, ft_sighandler);
	signal(SIGQUIT, ft_sighandler);
	ft_init(&tool, env, &data);
	while (1)
	{
		data.prompt = prompt(env);
		if (!data.prompt[0])
			ft_puterr(32);
		else if (parser(&data))
		{
			execution(&data.head, &tool.env, &data.exe_state);
			print_final_data(data.head, &data.exe_state);
		}
		else
			ft_puterr(14);
	}
	(void)ac;
	(void)av;
	return (0);
}
