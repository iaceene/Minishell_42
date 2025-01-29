/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:38:30 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/29 18:52:45 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <libc.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <string.h>

char *ft_strchr(char *s, char c);
int ft_strlen(char *s);
char *ft_strdup(char *s);

char	*ft_strtrim(char *s1, char set)
{
    int i;

	if ((!s1 && !set) || !s1)
		return (NULL);
	if (s1 && !set)
		return (ft_strdup(s1));
    i = 0;
    char *s = ft_strchr(s1, '.');
    if (!s)
        return (NULL);
    *s = '\0';
    return (s1);
}

int	ft_strcheck(char *str, char *word, size_t index)
{
	size_t	i;
	size_t	word_len;

	word_len = ft_strlen(word);
	i = 0;
	while (word[i] && str[index + i] == word[i])
		i++;
	return (word[i] == '\0');
}

char	*ft_strstr(char *haystack, char *needle)
{
	size_t	i;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			if (ft_strcheck(haystack, needle, i))
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
    {
        i++;
    }
    return (i);
}

char *ft_strdup(char *s)
{
    int i = 0;
    char *ret = ft_malloc(ft_strlen(s) + 1);
    while (s[i])
    {
        ret[i] = s[i]; 
        i++;
    }
    ret[i] = '\0';
    return (ret);
}

char *ft_join_params(char *user, char *sep, char *dis, char *dock)
{
    if (!user || !sep || !dis)
        return (exit(1), NULL);
    int i = 0;
    char *cli = ft_malloc (ft_strlen(user) + ft_strlen(sep) + ft_strlen(dis) + ft_strlen(dock) + 1);
    while (user[i])
    {
        cli[i] = user[i];
        i++;
    }
    int j = 0;
    while (sep[j])
    {
        cli[i] = sep[j];
        i++;
        j++;
    }
    j = 0;
    while (dis[j])
    {
        cli[i] = dis[j];
        i++;
        j++;
    }
    j = 0;
    while (dock[j])
    {
        cli[i] = dock[j];
        i++;
        j++;
    }
    cli[i] = '\0';
    return (cli);
}

char *ft_strchr(char *s, char c)
{
    int i = 0;
    while (s[i])
    {
        if (c == s[i])
            return (s + i);
        i++;
    }
    return (NULL);
}

char *ft_get_user(char **env)
{
    int i = 0;
    int flag = 0;
    while (env[i])
    {
        if (ft_strstr(env[i], "LOGNAME"))
        {
            flag = 1;
            break ;
        }
        i++;
    }
    if (flag == 0)
        return (NULL);
    return (ft_strdup(ft_strchr(env[i], '=') + 1));
}

char *ft_get_sission(char **env)
{
    int i = 0;
    int flag = 0;
    while (env[i])
    {
        if (ft_strstr(env[i], "SESSION_MANAGER"))
        {
            flag = 1;
            break ;
        }
        i++;
    }
    if (flag == 0)
        return (NULL);
    return (ft_strdup(ft_strtrim(ft_strchr(env[i], '/') + 1, '.')));
}

char *ft_get_cli(char **env)
{
    char *user;
    char *desktop;
    char *cli;

    user = ft_get_user(env);
    if (!user)
        user = ft_strdup("USER");
    desktop = ft_get_sission(env);
    if (!desktop)
        desktop = ft_strdup("1337");
    cli = ft_join_params(user, "@", desktop, ">> ");
    return (cli);
}

char *prompt(char *cli)
{
	char *s;
	s = readline(cli);
    return (free(s), NULL);
}    
    

void ft_sighandler(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
	else
	{
		ft_malloc (-1);
		exit(1);
	}
}

int main(int ac, char **av, char **env)
{
    char *cli = ft_get_cli(env);
    signal(SIGINT, ft_sighandler);
    signal(SIGQUIT, ft_sighandler);
    while (1)
        prompt(cli);
    return (0);
}