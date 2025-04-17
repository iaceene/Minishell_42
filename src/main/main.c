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

void	ft_init(t_tool *tool, char **env, t_data *data)
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

void	return_spaces(char *tmp)
{
	int	i;

	i = 0;
	if (!tmp)
		return ;
	while (tmp[i])
	{
		if (tmp[i] == -13)
			tmp[i] = ' ';
		i++;
	}
}

void	check_and_return_sp(t_cmd *head)
{
	int	i;

	while (head)
	{
		if (head->type == COMMAND)
		{
			i = 0;
			while (head->cmd[i])
			{
				return_spaces(head->cmd[i]);
				i++;
			}
		}
		head = head->next;
	}
}

void	input_prc(t_data	*data, t_tool *tool)
{
	int	state;

	(signal(SIGINT, ft_sighandler), signal(SIGQUIT, SIG_IGN));
	data->prompt = prompt(data->env, &data->exe_state);
	if (data->prompt[0])
	{
		state = parser(data);
		if (state == 1)
		{
			check_and_return_sp(data->head);
			execution(&data->head, &tool->env, &data->exe_state);
			close_fds(data->head);
		}
		else if (state == -99)
			close_fds(data->head);
		else if (state == 433)
			return ;
		else if (state == 0)
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

	data.env = env;
	ft_init(&tool, env, &data);
	data.final_env->data = &data;
	while (1337)
		input_prc(&data, &tool);
	(void)ac;
	(void)av;
	return (0);
}
