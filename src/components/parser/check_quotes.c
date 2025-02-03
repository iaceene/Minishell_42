/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 22:05:42 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/03 01:15:30 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parser.h"


int check_quotes(char *str)
{
    int n_sing;
    int n_doub;
    int i;

    n_sing = 0;
    n_doub = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '"')
            n_doub++;
        if (str[i] == '\'')
            n_sing++;
        i++;
    }
    if (n_sing % 2 || n_doub % 2)
        return (1);
    return (0);
}

int check_parentheses(char *str)
{
    int i;
    int n_left;
    int n_right;

    i = 0;
    n_right = 0;
    n_left = 0;
    while (str[i])
    {
        if (str[i] == ')')
            n_left++;
        if (str[i] == '(')
            n_right++;
        i++;
    }
    if (n_left != n_right)
        return (1);
    return (0);
}

int ft_find(char *str, char tofind)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == tofind)
            return (1);
        i++;
    }
    return (0);
}
