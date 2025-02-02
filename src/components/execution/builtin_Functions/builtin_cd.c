/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:04:09 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/27 13:07:01 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"


static int change_to_home_directory(t_env **env)
{
    char *home = get_value_env(*env, "HOME");
    if (!home)
    {
        perror("bash: cd: HOME not set\n");
        exitstatus(1, 1);
        return (1);
    }
    if (chdir(home) == -1)
    {
        perror("bash: cd: ");
        perror(home);
        perror(": No such file or directory\n");
        exitstatus(1, 1);
        return (1);
    }
    change_value_env(env, "OLDPWD", ft_strdup(get_value_env(*env, "PWD")));
    change_value_env(env, "PWD", ft_strdup(home));
    return (1);
}

static int change_to_previous_directory(t_env **env)
{
    char *oldpwd = get_value_env(*env, "OLDPWD");
    if (!oldpwd)
    {
        perror("bash: cd: OLDPWD not set\n");
        exitstatus(1, 1);
        return (1);
    }
    if (chdir(oldpwd) == -1)
    {
        perror("bash: ");
        perror(oldpwd);
        perror(": No such file or directory\n");
        exitstatus(1, 1);
        return (1);
    }
    change_value_env(env, "OLDPWD", ft_strdup(get_value_env(*env, "PWD")));
    change_value_env(env, "PWD", ft_strdup(oldpwd));
    return (1);
}

static int handle_special_cd_cases(t_env **env, char *path)
{
    if (!ft_strncmp(path, "~", 1))
        return change_to_home_directory(env);
    else if (!ft_strncmp(path, "-", 1))
        return change_to_previous_directory(env);
    return (0);
}

static int check_directory_exists(char *path)
{
    DIR *dir = opendir(path); 
    if (!dir)
    {
        perror("bash: cd: ");
        perror(path);
        perror(": ");
        perror("");
        exitstatus(1, 1);
        return (1);
    }
    closedir(dir);
    return (0);
}

void builtin_cd(char **args, t_env **env)
{
    if (!args[1] || !handle_special_cd_cases(env, args[1]))
    {
        if (args[1] && check_directory_exists(args[1]))
            return ;
        if (chdir(args[1]) == -1)
        {
            perror("bash: cd: ");
            perror(args[1]);
            perror(": ");
            perror("");
            exitstatus(1, 1);
            return ;
        }
    }
    change_value_env(env, "OLDPWD", ft_strdup(get_value_env(*env, "PWD")));
    char *new_pwd = getcwd(NULL, 0);
    change_value_env(env, "PWD", ft_strdup(new_pwd));
    return ;
}
