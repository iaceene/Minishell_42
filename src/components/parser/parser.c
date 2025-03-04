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

int parser(t_data *data)
{
	t_node *tock_data;

	tock_data = lexer_init(data->prompt);
	if (!tock_data)
		return (0);
	if (syntax_checker(tock_data) == -1)
		return (0);
	else
		data->head = data_maker(tock_data, data->final_env);
	if (!data->head)
		return (0);
	return (1);
}
