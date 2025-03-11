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



// final struct

typedef enum {
	COMMAND,       // Command or argument
	WORD,            /// for expanding
	PIPE,       // |
	APPEND,		// >>
	HERDOC,		// <<
	RIGHT_RED,	// >
	LEFT_RED,	// <
	SIN_QUOTE,  // '
	DOB_QUOTE, // "
	DOLLAR,     // $
	OPEN_PAR,  // (
	CLOSE_PAR, // )
	IN_FILE,
	OUT_FILE,
	SIMPLE_FILE,
	NIL /// this is NULL node
} TokenType;

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
void	exit_the_shell(int state);
char	*ft_join_params(char *user, char *dis);
char	*prompt(char **env);
//*****************************signals********************************
// void	ft_handle_signals(int sig);
void	ft_init_signals(void);
void	ft_sighandler(int sig);
// ****************************herdoc****************************
char *expand_heredoc_input(char *input, t_env *env, int exit_code);
void process_here_doc(char *delimiter, int *pipe_fd, t_env *env, int exit_code);


typedef struct s_cmd
{
	TokenType		type;
	char			*value;
	char			**cmd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char	**env;
	t_cmd	*head;
	t_env	*final_env;
	char	*prompt;
}	t_data;



/*****************Parser****************/
int		parser(t_data *data);






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
char	*ft_strjoin(char  *s1, char  *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);
size_t	ft_strlen(const char *str);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
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