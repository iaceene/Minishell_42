/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 22:07:36 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/31 18:02:18 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void    clear_terminal(void)
{
    write(1, "\033[H\033[J", 6);;
}

char **get_path(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (ft_strstr(env[i], "PATH"))
        {
            if (ft_strstr(env[i], "bin"))
                return(ft_split(ft_strstr(env[i], "/usr/bin"), ':'));
        }
        i++;
    }
    return (NULL);
}

void check_path(t_data *data)
{
    char **tmp;

    tmp = get_path(data->env);
    data->bin_path = tmp[0];
    printf("%s\n", data->bin_path);
    if (!data->bin_path || access(ft_strjoin(data->bin_path, "/ls"), X_OK) == -1)
        return (exit_the_shell(1));
}
