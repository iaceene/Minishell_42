#include <libc.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <string.h>

typedef struct s_gb
{
	void		*ptr;
	struct s_gb	*next;
}t_gb;

typedef struct s_data
{
	char **env;
	char *bin_path;
}t_data;

char	*ft_strstr(char *haystack, char *needle);
void	exit_the_shell(int state);
char	*ft_strtrim(char *s1, char *set);
char	*ft_join_params(char *user, char *sep, char *dis, char *dock);
void	*ft_malloc(ssize_t len);
char	*ft_get_cli(char **env);
void	ft_puterr(int state);
int		ft_strncmp(char *str1, char *str2, size_t n);
char	*ft_strchr(char *s, char c);
int		ft_strlen(char *s);
char	*prompt(char **env);
char	**ft_split(char const *s, char c);
void	ft_sighandler(int sig);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
void	check_path(t_data *data);
void    clear_terminal(void);
char	*get_next_line(int fd);