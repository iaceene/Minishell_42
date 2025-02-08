/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:23:52 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/26 16:51:29 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../../include/execution.h"
#include "../../../../include/minishell.h"
#include "../../../../include/parser.h"

void ft_execute_heredoc(t_cmd *cmd, t_env **env, int *exit_status)
{
    int temp_fd = open(".temp_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (temp_fd == -1)
    {
        *exit_status = 1;
        perror("heredoc");
        return;
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while (1)
    {
        write(1, "> ", 2);
        read = getline(&line, &len, stdin);
        if (read == -1)
            break;
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';
        if (strcmp(line, &cmd->value[1]) == 0)
            break;
        write(temp_fd, line, strlen(line));
        write(temp_fd, "\n", 1);
    }
    free(line);
    close(temp_fd);
    int fd_in = open(".temp_heredoc", O_RDONLY);
    if (fd_in == -1)
    {
        *exit_status = 1;
        perror("heredoc");
        unlink(".temp_heredoc");
        return;
    }
    int stdin_backup = dup(STDIN_FILENO);
    dup2(fd_in, STDIN_FILENO);
    close(fd_in);
    execution_cmd(cmd->value, env, exit_status);
    dup2(stdin_backup, STDIN_FILENO);
    close(stdin_backup);
    unlink(".temp_heredoc");
}

void ft_execute_redirection_out(t_cmd *cmd, t_env **env, int *exit_status)
{
    int fd;
    if (cmd->type == APPEND)
        fd = open(&cmd->value[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        fd = open(&cmd->value[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        *exit_status = 1;
        perror("redirection");
        return;
    }
    int stdout_backup = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    execution_cmd(cmd->value, env, exit_status);
    dup2(stdout_backup, STDOUT_FILENO);
    close(stdout_backup);
}

void ft_execute_redirection_in(t_cmd *cmd, t_env **env, int *exit_status)
{
    int fd = open(&cmd->value[1], O_RDONLY);
    if (fd == -1)
    {
        *exit_status = 1;
        perror("redirection");
        return;
    }
    int stdin_backup = dup(STDIN_FILENO);
    dup2(fd, STDIN_FILENO);
    close(fd);
    execution_cmd(cmd->value, env, exit_status);
    dup2(stdin_backup, STDIN_FILENO);
    close(stdin_backup);
}

void execution(t_cmd *head, t_env **env, int *exit_status)
{
    if (!head)
        return;
    t_cmd *current = head;
    int cmd_count = 0;
    t_cmd **commands = NULL;

    // Count commands excluding pipes
    while (current)
    {
        if (current->type != PIPE)
            cmd_count++;
        current = current->next;
    }

    if (cmd_count == 0)
        return;

    commands = ft_malloc(sizeof(t_cmd *) * cmd_count);
    if (!commands)
        error_and_exit("Memory allocation failed", 1);

    // Fill commands array
    current = head;
    int i = 0;
    while (current)
    {
        if (current->type != PIPE)
        {
            commands[i] = current;
            // Check if next command is a redirection
            if (current->next && (current->next->type == RIGHT_RED || 
                current->next->type == APPEND || 
                current->next->type == LEFT_RED ||
                current->next->type == HERDOC))
            {
                current = current->next;  // Skip the redirection token
            }
            i++;
        }
        current = current->next;
    }

    // Execute commands
    if (cmd_count > 1)
        ft_pipex(commands, cmd_count, env, exit_status);
    else if (commands[0]->type == APPEND || commands[0]->type == RIGHT_RED)
        ft_execute_redirection_out(commands[0], env, exit_status);
    else if (commands[0]->type == LEFT_RED)
        ft_execute_redirection_in(commands[0], env, exit_status);
    else if (commands[0]->type == HERDOC)
        ft_execute_heredoc(commands[0], env, exit_status);
    else
        execution_cmd(commands[0]->value, env, exit_status);

    free(commands);
}