/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:05:05 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/27 13:06:31 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

void builtin_pwd()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        write(1, cwd, ft_strlen(cwd));
        write(1, "\n", 1);
    }
    else
    {
        write(2, "pwd: error: cannot retrieve current directory\n", 46);
    }
}
