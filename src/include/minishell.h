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
void	exit_the_shell(void);
char	*ft_strtrim(char *s1, char set);
char	*ft_join_params(char *user, char *sep, char *dis, char *dock);
void	*ft_malloc(ssize_t len);
char	*ft_get_cli(char **env);
int		ft_strncmp(char *str1, char *str2, size_t n);
char	*ft_strchr(char *s, char c);
int		ft_strlen(char *s);
char	*prompt(char *cli);
void	ft_sighandler(int sig);
char	*ft_strdup(char *s);