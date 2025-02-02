/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:01:58 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/02 22:00:17 by yaajagro         ###   ########.fr       */
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

int check_left_red(char **str);
int check_right_red(char **str);
int check_pip(char **str);
int check_condition(char *str);

int check_operators(char *str)
{
    char **left_red;
    char **right_red;
    char **pip;

    if (ft_find(str, '<'))
    {
        left_red = ft_split(str, '<');
        return (check_left_red(left_red));
    }
    if (ft_find(str, '>'))
    {
        right_red = ft_split(str, '>');
        return (check_right_red(right_red));
    }
    if (ft_find(str, '|'))
    {
        pip = ft_split(str, '|');
        return (check_pip(pip));   
    }
    // return (check_condition(str));
    return (0);
}

int check_syntax(char *str)
{
    int err;

    err = check_quotes(str);
    err += check_parentheses(str);
    err += check_operators(str);
    if (!str || err != 0)
        return (-1);
    return (1);
}


int check_left_red(char **str)
{
    int i;

    i = 0;
    printf("<\n");
    while (str[i])
    {
        if (ft_find(str[i], ' ') || )
        i++;
    }
    return (0);
}

int check_right_red(char **str)
{
    int i;

    i = 0;
    printf(">\n");
    while (str[i])
    {
        printf("%s\n", str[i]);
        i++;
    }
    return (0);
}

int check_pip(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        printf("%s\n", str[i]);
        i++;
    }
    return (i % 2);
}

// int ft_check_and(char *str)
// {
//     char **
// }

// int check_condition(char *str)
// {
//     int i;
//     int err;

//     i = 0;
//     err = 0;
//     while (str[i])
//     {
//         if (str[i] == '&' && str[i + 1] != '&')
//             return (1);
//         if (str[i] == '&' && str[i + 1] == '&')
//             err += ft_check_and(str);
//         if (str[i] == '|' && str[i + 1] == '|')
//             err += ft_check_or(str);
//         i++;
//     }
//     if (err != 0)
//         return (1);
//     return (0);
// }
