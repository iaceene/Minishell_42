#include "libc.h"

typedef struct s_gb
{
	void		*ptr;
	struct s_gb	*next;
}t_gb;

char	*ft_strnstr(char *haystack, char *needle, size_t len);
// size_t  ft_strlen(char *s);
void	*ft_malloc(ssize_t len);