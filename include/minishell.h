/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:22:25 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/31 18:38:07 by iezzam           ###   ########.fr       */
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

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

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


typedef struct s_data
{
	char **env;
	t_env *env_var; /// use this instead of env
	t_shell *shell;
	char *prompt;
}t_data;

typedef struct s_gb
{
	void		*ptr;
	struct s_gb	*next;
}t_gb;







/*****************                       Execution                            ****************/

//  src/components/execution/execution.c
void	execution(t_shell *shell);
// buildin
void	builtin_cd(char **args, char ***env);
void	builtin_echo(char **args);
void	builtin_env(char **env);
void	builtin_exit(char **args);
void	builtin_export(char **args, char ***env);
void	builtin_pwd(void);
void	builtin_unset(char **args, char ***env);
void	execute_builtin(t_shell *shell);


//  src/components/execution/creat_child.c
void	child2(t_shell *data, int **wr_pipe);
void	child1(t_shell *data, int **wr_pipe);
// void    child_intermediate(t_shell data, char **av, int **pipes, char **env);
void	child_intermediate(t_shell *data, int **pipes);

//  src/components/execution/error_handling.c
void	ft_free_string(char **str);
void	error_and_exit(const char *str, int exite);

// void    close_fd(int fd, char *str);
void	close_fd(t_redirect *data);
void	cleanup_shell(t_shell *shell);

//  src/components/execution/pipex.c
// void		redirect_fd(int from_fd, int to_fd, const char *str);
void	close_all_pipe(int **pipes, int num_cmd);
void	free_all_pipe(int **pipes, int i);
void	ft_pipex(t_shell *shell);


//src/components/execution/find_command_path.c
char	*find_command_path(char *cmd, char **env);
void	execute_cmd(char **cmd, char **env);


//  src/components/execution/creat_env/creat_env.c
void	free_env(t_env *env_list);
char	**convert_env_to_array(t_env *env_list);
t_env	*ft_env_create(char **envp);

//src/components/execution/signals/signals.c
void	ft_handle_signals(int sig);
void	ft_init_signals(void);







/*****************                       Parser                            ****************/
//src/components/parser
	//creat_env
t_env	*ft_env_create(char **envp);
int		parser(t_data *data);









	//prompt
char	*ft_get_cli(char **env);
char	*get_next_line(int fd);
void	exit_the_shell(int state);
char	*ft_join_params(char *user, char *sep, char *dis, char *dock);
void	ft_sighandler(int sig);
char	*prompt(char **env);






//src/lib
		//memory
void	*ft_malloc(ssize_t len);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_isspace(int c);
char	**ft_split_shell(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strcat(char *dest, char *src);
char	*ft_strchr(char *s, char c);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strstr(char *haystack, char *needle);
char	*ft_strtok(char *str, const char *delim);
char	*ft_strtrim(char *s1, char *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_puterr(int state);









#endif