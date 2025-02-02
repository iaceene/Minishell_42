/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:01:58 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/02 22:06:05 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parser.h"

int check_syntax(char *str)
{
    int err;

    err = check_quotes(str);
    err += check_parentheses(str);
    // err += check_operators(str);
    if (!str || err != 0)
        return (-1);
    return (1);
}
