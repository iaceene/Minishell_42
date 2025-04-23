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

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/param.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef enum e_TokenType
{
	COMMAND,
	WORD,
	PIPE,
	APPEND,
	HERDOC,
	RIGHT_RED,
	LEFT_RED,
	SIN_QUOTE,
	DOB_QUOTE,
	DOLLAR,
	OPEN_PAR,
	CLOSE_PAR,
	IN_FILE,
	OUT_FILE,
	SIMPLE_FILE,
	NIL
}	t_TokenType;

typedef struct s_env
{
	char			*key;
	struct s_data	*data;
	char			*value;
	struct s_env	*next;
	int				visible;
	char			**a_ven;
	bool			flag;
}	t_env;

typedef struct s_cmd
{
	t_TokenType		type;
	bool			pip_infront;
	int				fd_herdoc;
	char			*value;
	char			*file_name;
	char			**cmd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char	**env;
	int		exe_state;
	t_cmd	*head;
	t_env	*final_env;
	char	*prompt;
}	t_data;

char	*ft_get_cli(char **env);
void	exit_the_shell(int state);
char	*ft_join_params(char *user, char *dis);
char	*prompt(char **env, int *ex);
int		ft_get_signum(void);
void	ft_sighandler(int sig);
char	*find_command_path(char *cmd, char **env);
char	*find_executable_in_path(char *path, char *cmd);
char	*get_path_variable(char **env);
int		parser(t_data *data);
void	*ft_malloc(ssize_t len);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_isspace(int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(char *s, char c);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
size_t	ft_strlen(const char *str);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strstr(char *haystack, char *needle);
char	*ft_itoa(int n);
char	*ft_strtok(char *str, const char *delim);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_print_err(char *s);
void	ft_puterr(int state);
bool	is_same(char *s1, char *s2);
int		exitstatus(int newstatus, int flag);

#endif