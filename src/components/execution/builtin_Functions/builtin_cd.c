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

void builtin_cd(char **args, char ***env)
{
    // while (*env)
    // {
    //     fprintf(stderr, "----env: %s\n", (*env)[0]);
    //     env++;
    // }
    char *path = args[1];
    char cwd[1024];
    char *old_pwd;

    if (!path)
    {
        path = getenv("HOME");
        if (!path)
        {
            write(2, "cd: HOME not set\n", 17);
            return;
        }
    }
    if (!getcwd(cwd, sizeof(cwd)))
    {
        write(2, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 108);
        return;
    }
    old_pwd = ft_strdup(cwd);
    if (chdir(path) != 0)
    {
        write(2, "cd:  no such file or directory: ", 32);
        write(2, path, ft_strlen(path));
        write(2, "\n", 1);
        free(old_pwd);
        return;
    }
    int updated = 0;
    int i = 0;
    while ((*env)[i])
    {
        if (ft_strncmp((*env)[i], "OLDPWD=", 7) == 0)
        {
            free((*env)[i]);
            (*env)[i] = malloc(ft_strlen("OLDPWD=") + ft_strlen(old_pwd) + 1);
            if ((*env)[i])
            {
                strcpy((*env)[i], "OLDPWD=");
                strcat((*env)[i], old_pwd);
            }
            updated = 1;
            break;
        }
        i++;
    }
    if (!updated)
    {
        int count = 0;
        while ((*env)[count])
            count++;
        *env = realloc(*env, sizeof(char *) * (count + 2));
        (*env)[count] = malloc(ft_strlen("OLDPWD=") + ft_strlen(old_pwd) + 1);
        if ((*env)[count])
        {
            ft_strcpy((*env)[count], "OLDPWD=");
            ft_strcat((*env)[count], old_pwd);
        }
        (*env)[count + 1] = NULL;
    }
    free(old_pwd);
    updated = 0;
    if (getcwd(cwd, sizeof(cwd)))
    {
        int i = 0;
        while ((*env)[i])
        {
            if (ft_strncmp((*env)[i], "PWD=", 4) == 0)
            {
                free((*env)[i]);
                (*env)[i] = malloc(ft_strlen("PWD=") + ft_strlen(cwd) + 1);
                if ((*env)[i])
                {
                    ft_strcpy((*env)[i], "PWD=");
                    ft_strcat((*env)[i], cwd);
                }
                updated = 1;
                break;
            }
            i++;
        }
        if (!updated)
        {
            int count = 0;
            while ((*env)[count])
                count++;
            *env = realloc(*env, sizeof(char *) * (count + 2));
            (*env)[count] = malloc(ft_strlen("PWD=") + ft_strlen(cwd) + 1);
            if ((*env)[count])
            {
                ft_strcpy((*env)[count], "PWD=");
                ft_strcat((*env)[count], cwd);
            }
            (*env)[count + 1] = NULL;
        }
    }
    else
    {
        write(2, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", 108);
    }
}
