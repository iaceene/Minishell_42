/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:36:43 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/02 20:44:42 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H


# define SUCCESS 0
# define FAILED 1

# define SPACE ' '
# define EQUAL '='




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
	char			*key;
	char			*value;
	struct s_env	*next;

	char			*pwd;
	char			**envp;
}			t_env;

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
}t_gb;




/*****************                       Execution                            ****************/
void	execution(t_shell *shell);
//*******************buildin****************************
int		builtin_cd(char **cmd_2d, t_env **env, int *exit_status);
void	builtin_echo(char **args);
void	builtin_env(char **env);
void	builtin_exit(char **args);
void	builtin_export(char **args, char ***env);
char	*ft_get_cwd(char *tojoin, int i);
void	builtin_pwd(void);
void	builtin_unset(char **args, char ***env);
void	execute_builtin(t_shell *shell);
//**********************creat_env******************************
t_env	*ft_env_create(char **envp);

/* env_utils.c */
int		count_env_list(t_env *env_list);
char	*ft_env_search(t_env *env, const char *key);
char	**convert_env_to_array(t_env *env_list);

/* env_manage.c */
void	ft_env_delete(t_env **env, char *key);
void	ft_env_add(t_env **env, char *key, char *value, int overwrite);
int		ft_env_update(t_env **env, char *key, char *value, int overwrite);
//****************************creat_child**********************
void	child2(t_shell *data, int **wr_pipe);
void	child1(t_shell *data, int **wr_pipe);
void	child_intermediate(t_shell *data, int **pipes);
//**********************error_handling***********************
void	ft_free_string(char **str);
void	error_and_exit(const char *str, int exite);
void	close_fd(t_redirect *data);
void	cleanup_shell(t_shell *shell);
//***********************pipex****************************
// void		redirect_fd(int from_fd, int to_fd, const char *str);
void	close_all_pipe(int **pipes, int num_cmd);
void	free_all_pipe(int **pipes, int i);
void	ft_pipex(t_shell *shell);
//****************************find_command_path***************************
char	*find_command_path(char *cmd, char **env);
void	execute_cmd(char **cmd, char **env);





#endif