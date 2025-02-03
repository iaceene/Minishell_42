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

#include "../../../include/parser.h"

int parser(t_data *data)
{
    t_node *tock_data;

    tock_data = lexer_init(data->prompt);
    if (syntax_checker(tock_data) == -1)
        printf ("Syntax error\n");
    else
        printf ("systax valid\n");
    return (11);
}
