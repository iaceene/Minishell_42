/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:22:25 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/31 17:33:44 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINI_SHELL_H
#define MINI_SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <signal.h>

#include <dirent.h>


typedef struct s_command
{
	char **args;
	char *path;
	char *input_path;
	char *output_path;
	int append;
} t_command;

typedef struct s_redirect
{
	char *infile;
	char *outfile;
	int fdin;
	int fdout;
	int num_cmds;
	int heredoc;
} t_redirect;

typedef struct s_shell
{
	char **env;
	t_env **envp;
	t_command *commands;
	t_redirect *redirect;
	int num_cmds;
	int last_exit;
	int in_pipe;
} t_shell;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_data
{
	char **env;
	t_env *env_var; /// use this instead of env
	char *bin_path;
}t_data;

typedef struct s_gb
{
	void		*ptr;
	struct s_gb	*next;
}t_gb;



//src/components/parser
	//creat_env
t_env	*ft_env_create(char **envp);
	//prompt
char	*ft_get_cli(char **env);
char	*get_next_line(int fd);
void	exit_the_shell(int state);
char	*ft_join_params(char *user, char *sep, char *dis, char *dock);
int		ft_strncmp(char *str1, char *str2, size_t n);
char	*ft_strchr(char *s, char c);
void	ft_sighandler(int sig);
void	check_path(t_data *data);
void    clear_terminal(void);
char	*prompt(char **env);






//src/lib
		//memory
void	*ft_malloc(ssize_t len);
char	**ft_split(char const *s, char c);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
char	*ft_strstr(char *haystack, char *needle);
char	*ft_strtrim(char *s1, char *set);
void	ft_puterr(int state);







#endif