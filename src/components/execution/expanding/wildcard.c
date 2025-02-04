 
#include "../../../../include/execution.h"


static char	**ft_create_dp(int row, int col)
{
	char	**dp;
	int		r;
	int		c;

	dp = (char **)malloc(sizeof(char *) * (row + 1));
	if (!dp)
		return (NULL);
	r = -1;
	while (++r < row)
		dp[r] = (char *)malloc(sizeof(char) * col);
	r = -1;
	while (++r < row)
	{
		c = -1;
		while (++c < col)
			dp[r][c] = 0;
	}
	dp[r] = NULL;
	dp[0][0] = '1';
	return (dp);
}

static	int	ft_free_dp_and_return(char **dp, int s_len, int p_len)
{
	int	res;

	res = dp[s_len][p_len] == '1';
	return (res);
}

void	ft_list_cwd(t_list **head)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (dir == NULL)
	{
		perror("Error");
		return ;
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
			ft_lstadd_back(head, ft_lstnew(ft_strdup(entry->d_name)));
		entry = readdir(dir);
	}
	if (closedir(dir) != 0)
		perror("Error");
}

int	get_matching_files(t_list **head, char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	int				found_match;

	found_match = 0;
	dir = opendir(".");
	if (dir == NULL)
	{
		perror("Error");
		return (0);
	}
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.' && ft_is_match(entry->d_name, pattern))
		{
			ft_lstadd_back(head, ft_lstnew(ft_strdup(entry->d_name)));
			found_match = 1;
		}
		entry = readdir(dir);
	}
	if (closedir(dir) != 0)
		perror("Error");
	return (found_match);
}

int	ft_is_match(char *s, char *p)
{
	char	**dp;
	int		s_len;
	int		p_len;
	int		i;
	int		j;

	s_len = ft_strlen(s);
	p_len = ft_strlen(p);
	dp = ft_create_dp(s_len + 1, p_len + 1);
	i = -1;
	while (++i <= s_len)
	{
		j = 0;
		while (++j <= p_len)
		{
			if (p[j - 1] == '*')
			{
				if (dp[i][j - 1] == '1' || (i > 0 && dp[i - 1][j] == '1'))
					dp[i][j] = '1';
			}
			else if (i > 0 && (p[j - 1] == s[i - 1]))
				dp[i][j] = dp[i - 1][j - 1];
		}
	}
	return (ft_free_dp_and_return(dp, s_len, p_len));
}
