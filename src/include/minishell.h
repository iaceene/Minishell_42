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

char	*ft_strnstr(char *haystack, char *needle, size_t len);
char	*ft_join_params(char *user, char *sep, char *dis, char *dock);
void	*ft_malloc(ssize_t len);
char	*ft_get_cli(char **env);
char	*ft_strchr(char *s, char c);
int		ft_strlen(char *s);
void	ft_sighandler(int sig);
char	*ft_strdup(char *s);