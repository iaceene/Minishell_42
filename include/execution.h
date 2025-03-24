/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneki <kaneki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:36:43 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/24 13:07:09 by kaneki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

/************************* Forward Declarations *************************/

# include "minishell.h"

# define SUCCESS 0
# define FAILED 1
# define EQUAL '='

/************************* Structures *************************/

typedef struct s_pipe
{
	int		end[2];
	int		end2[2];
	int		indice;
	int		in;
}	t_pipe;

typedef struct s_exec
{
	TokenType		type;
	char			*value;
	char			**s;
	struct s_exec	*next;
}	t_exec;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_gb
{
	void		*ptr;
	struct s_gb	*next;
}	t_gb;

typedef struct s_redirect
{
	char	*infile;
	char	*outfile;
	int		fdin;
	int		fdout;
	int		num_cmds;
	int		heredoc;
}	t_redirect;

typedef struct s_tool
{
	t_env	*env;
}	t_tool;

typedef struct s_pipex_data
{
	int	infile;
	int	outfile;
	int	pipe_fd[2];
	int	prev_pipe_read;
	int	cmd_count;
	int	current_cmd;
	int	fd_count;
}	t_pipex_data;

typedef struct s_export
{
	int		pos;
	char	*key_part;
	char	*value_part;
	int		has_equal;
	int		is_append;
	char	*existing_value;
}	t_export;

/************************* Execution Functions *************************/

void	execution(t_cmd **head, t_env **env, int *exit_status);
void	execution_cmd(char **cmd, t_env **env, int *exit_status);
void	child1(t_cmd *cmd, int **pipes, int pipe_count, t_env **env);
void	child_last(t_cmd *cmd, int **pipes, int pipe_count, t_env **env);
void	ft_free_string(char **str);
void	error_and_exit(const char *str, int exite);
void	close_fd(t_redirect *data);
void	close_all_pipe(int **pipes, int num_cmd);
void	free_all_pipe(int **pipes, int i);
void	ft_pipex(t_cmd *commands, t_env **env, int *exit_status);
char	*find_command_path(char *cmd, char **env);
void	execute_cmd(char **cmd, char **env, int *exit_status);
void	handle_redirection(t_pipex_data *data);
void	cleanup_child_fds(t_pipex_data *data);
int		count_commands(t_cmd *cmd);
int		handle_file_redirection(t_cmd *cmd, int *infile, int *outfile, \
	t_pipex_data *data);

/************************* Built-in Functions *************************/

int		builtin_cd(char **arg, t_env **env, int *exit_status);
void	builtin_echo(char **args);
void	builtin_env(t_env *env, char **arg, int *exit_status);
void	ft_export_help(char *cmd, t_env **env, int *exit_status);
void	print_export_error(char *slice1, char *slice2, int equal, int append);
void	builtin_export(t_env **env, char **arg, int *exit_status);
char	*ft_get_cwd(char *tojoin, int i);
void	builtin_pwd(void);
void	builtin_unset(t_env **env, char **arg, int *exit_status);
int		ft_execute_builtins(char **arg, t_env **env, int *exit_status, t_pipex_data *data, int f_fd);

/************************* Environment Functions *************************/

int		ft_env_add(t_env **env, char *key, char *value, int visible);
void	ft_env_clear(t_env **env);
char	**ft_env_create_2d(t_env *env);
t_env	*ft_env_create(char **ev);
void	ft_env_delete(t_env **env, char *key);
t_env	*ft_env_duplicate(t_env *env);
void	ft_print_env(t_env *env);
char	*ft_env_search(t_env *env, char *key);
int		ft_env_size(t_env *env);
int		ft_env_update(t_env **env, char *key, char *newval, int append_mod);

/************************* List Functions *************************/

t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst);

#endif