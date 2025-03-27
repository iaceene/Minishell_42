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
#include "../../include/execution.h"

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

void	close_fds(t_cmd *head)
{
	while (head)
	{
		if (head->type == HERDOC && head->fd_herdoc != -1)
			close(head->fd_herdoc);
		head = head->next;
	}
}

void	input_prc(t_data	*data, t_tool *tool)
{
	int	state;

	data->prompt = prompt(data->env);
	if (data->prompt[0])
	{
		state = parser(data);
		if (state == 1)
		{
			execution(&data->head, &tool->env, &data->exe_state);
			close_fds(data->head);
		}
		else if (state == -99)
		{
			close_fds(data->head);
			data->exe_state = 130;
		}
		else
		{
			ft_puterr(14);
			data->exe_state = 2;
		}
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
	data.final_env->data = &data;
	while (1337)
		input_prc(&data, &tool);
	(void)ac;
	(void)av;
	return (0);
}
