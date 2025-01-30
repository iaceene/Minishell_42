/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:48:34 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/30 21:19:26 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char *ft_strjoin(char *s1, char *s2)
{
    if (!s1 || !s2)
        return (NULL);
    int i = 0;
    int j = 0;
    char *ret = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    while (s1[i])
    {
        ret[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        ret[i] = s2[j];
        j++;
        i++;
    }
    ret[i] = '\0';
    return (ret);
}

void    clear_terminal(void)
{
    write(1, "\033[H\033[J", 6);;
}

char *get_path(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (ft_strstr(env[i], "PATH"))
        {
            if (ft_strstr(env[i], "bin"))
                return(ft_strtrim(ft_strstr(env[i], "/usr/bin"), ':'));
        }
        i++;
    }
    return (NULL);
}

void check_path(t_data *data)
{
    data->bin_path = get_path(data->env);
    if (!data->bin_path || access(ft_strjoin(data->bin_path, "/ls"), X_OK) == -1)
        return (exit_the_shell());
}

int main(int ac, char **av, char **env)
{
    t_data data;

    data.env = env;
    char *cli = ft_get_cli(env);
    check_path(&data);
    clear_terminal();
    signal(SIGINT, ft_sighandler);
    signal(SIGQUIT, ft_sighandler);
    while (1)
        prompt(cli);
    return (0);
}
