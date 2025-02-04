/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:36:43 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/04 15:28:15 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H
# include "minishell.h"


# define SUCCESS 0
# define FAILED 1

# define SPACE ' '
# define EQUAL '='


typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

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

// typedef struct s_env
// {
// 	char			*key;
// 	char			*value;
// 	struct s_env	*next;

// 	char			*pwd;
// 	char			**envp;
// }			t_env;

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
	t_env *env_var;
	t_shell *shell;
	char *prompt;
}t_data;

typedef struct s_gb
{
	void		*ptr;
	struct s_gb	*next;
}	t_gb;

typedef struct s_tool
{
	int			prac;
	int			quot;
	int			err;
	int			anderr;
	t_env		*env;
	t_gb	*grbg;
}	t_tool;

/************************* expand *************************/
typedef struct s_expand
{
	t_list	*head;
	int		quote;
	int		noting_before_quote;
	char	*buff_exp;
	char	*buff_env;
	int		i;
	int		found_star;
	int		found_another_char;
}	t_expand;


/*****************                       Execution                            ****************/
void	execution(t_tree *root, t_env **env, int *exit_status);
//*******************execute****************************
void	execution_cmd(char *cmd, t_env **env, int *exit_status);
//creat_child
void	child2(t_shell *data, int **wr_pipe);
void	child1(t_shell *data, int **wr_pipe);
void	child_intermediate(t_shell *data, int **pipes);
//error_handling
void	ft_free_string(char **str);
void	error_and_exit(const char *str, int exite);
void	close_fd(t_redirect *data);
void	cleanup_shell(t_shell *shell);
//pipex
// void		redirect_fd(int from_fd, int to_fd, const char *str);
void	close_all_pipe(int **pipes, int num_cmd);
void	free_all_pipe(int **pipes, int i);
void	ft_pipex(t_shell *shell);
//find_command_path
char	*find_command_path(char *cmd, char **env);
void	execute_cmd(char **cmd, char **env);
void	execution_cmd(char *cmd, t_env **env, int *exit_status);
//*******************buildin****************************

typedef struct s_export
{
    int     pos;
    char    *key_part;
    char    *value_part;
    int     has_equal;
    int     is_append;
    char    *existing_value;
}	t_export;
int		builtin_cd(char **cmd_2d, t_env **env, int *exit_status);
void	builtin_echo(char **args);
void	builtin_env(t_env *env, char **cmd_2d, int *exit_status);
void	builtin_exit(char **cmd_2d, int *exit_status, t_env **env);
void	ft_export_help(char *cmd, t_env **env, int *exit_status);
void	ft_export_error(char *slice1, char *slice2, int equal, int append);
void 	builtin_export(t_env **env, char **cmd_2d, int *exit_status);
char	*ft_get_cwd(char *tojoin, int i);
void	builtin_pwd(void);
void 	builtin_unset(t_env **env, char **cmd_2d, int *exit_status);
int		ft_execute_builtins(char **cmd_2d, t_env **env, int *exit_status);
/************************* env *************************/
int		ft_env_add(t_env **env, char *key, char *value, int visible);
void	ft_env_clear(t_env **env);
char	**ft_env_create_2d(t_env *env);
t_env	*ft_env_create(char **ev);
void	ft_env_delete(t_env **env, char *key);
t_env	*ft_env_duplicate(t_env *env);
void	ft_env_print(t_env *env);
char	*ft_env_search(t_env *env, char *key);
int		ft_env_size(t_env *env);
int		ft_env_update(t_env **env, char *key, char *newval, int append_mod);



/*****************Parser****************/
int		parser(t_data *data);




t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst);


#endif