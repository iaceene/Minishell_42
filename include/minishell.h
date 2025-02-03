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


# include <sys/param.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>
# include <limits.h>
# include <sys/wait.h>
# include <termios.h>

# define REDIRECTION 1
# define INPUT 2
# define PIPE 3
# define SINGL_AND 4
# define AND 5
# define OR 6
# define SINGLE_QUAT 7
# define DOUBLE_QUAT 8
# define APPEND_REDIRECTION 9
# define HERE_DOC 10
# define CLOSE_PARENTH 11
# define OPEN_PARENTH 12
# define OPERAND 0
# define OUTFILE -2
# define INFILE -3
# define LIMITER -4
# define OUTFILE_APPAND -5

# define L_TO_R 3
# define R_TO_L 2

enum e_peroirty
{
	open_par = 6 ,
	close_par = 6,
	and = 5,
	or = 5,
	pip = 3,
	redir = 1,
	appand = 1,
	here_doc = 1,
	input = 1
};


// *********************tree******************


typedef struct s_tree
{
	char			*value;
	int				prio;
	int				read;
	int				type;
	struct s_tree	*right;
	struct s_tree	*left;
}	t_tree;

/************************* env struct *************************/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	int				visible;
	char			**a_ven;
}	t_env;


/************************* her_doc struct *************************/
typedef struct s_expand_herdoc
{
	char	*buffer_env;
	char	*buffer_exp;
	int     i;
	int		exit_status;
	t_env	*env;
}	t_expand_herdoc;










// ********************prompt*************************
char	*ft_get_cli(char **env);
char	*get_next_line(int fd);
void	exit_the_shell(int state);
char	*ft_join_params(char *user, char *sep, char *dis, char *dock);
char	*prompt(char **env);
//*****************************signals********************************
// void	ft_handle_signals(int sig);
void	ft_init_signals(void);
void	ft_sighandler(int sig);
// ****************************herdoc****************************
char *expand_heredoc_input(char *input, t_env *env, int exit_code);
void process_here_doc(char *delimiter, int *pipe_fd, t_env *env, int exit_code);











// ***********************lib***************************
void	*ft_malloc(ssize_t len);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_isspace(int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	**ft_split_shell(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strcat(char *dest, char *src);
char	*ft_strchr(char *s, char c);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strstr(char *haystack, char *needle);
char	*ft_itoa(int n);
char	*ft_strtok(char *str, const char *delim);
char	*ft_strtrim(char *s1, char *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_print_err(char *s);
void	ft_puterr(int state);
int		exitstatus(int newstatus, int flag);


#include "execution.h"
#include "parser.h"

#endif