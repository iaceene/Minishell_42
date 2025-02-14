/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:13:16 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/26 15:43:13 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

void wait_for_processes(pid_t *pids, int cmd_count, int *exit_status)
{
    int last_status = 0;
    for (int i = 0; i < cmd_count; i++)
    {
        int status;
        waitpid(pids[i], &status, 0);
        if (i == cmd_count - 1)
            last_status = status;
    }
    if (WIFEXITED(last_status))
        *exit_status = WEXITSTATUS(last_status);
}

char *clean_filename(char *filename)
{
    if (!filename)
        return NULL;
    while (*filename == ' ')
        filename++;
    int len = strlen(filename);
    while (len > 0 && filename[len - 1] == ' ')
        filename[--len] = '\0';
    if (filename[0] == '\'' || filename[0] == '"')
        memmove(filename, filename + 1, strlen(filename));
    len = strlen(filename);
    if (len > 0 && (filename[len - 1] == '\'' || filename[len - 1] == '"'))
        filename[len - 1] = '\0';
    return filename;
}
void handle_redirections(t_cmd *cmd)
{
    t_cmd *redir = cmd;
    int fd = -1;
    char *filename = NULL;
    static int i = 0;
    if (cmd->type != COMMAND)
    {
        while (redir && (redir->type == LEFT_RED || redir->type == RIGHT_RED || 
                redir->type == APPEND || redir->type == HERDOC))
        {
            fprintf(stderr, "i: %d\n", i++);
            fprintf(stderr ,"redir->value: %s\n", redir->value);
            if (redir->next && redir->next->value)
            {
                char **split_filename = ft_split(redir->next->value, ' ');
                if (!split_filename || !split_filename[0])
                {
                    fprintf(stderr, "minishell: invalid redirection\n");
                    exit(1);
                }
                
                filename = clean_filename(split_filename[0]);
                fprintf(stderr, "filename: %s\n", filename);
                if (redir->type == LEFT_RED)
                {
                    fd = open(filename, O_RDONLY);
                    if (fd == -1)
                    {
                        fprintf(stderr, "minishell: %s: No such file or directory\n", filename);
                        exit(1);
                    }
                    dup2(fd, STDIN_FILENO);
                }
                else if (redir->type == RIGHT_RED)
                {
                    fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
                    if (fd == -1)
                    {
                        fprintf(stderr, "minishell: %s: Permission denied\n", filename);
                        exit(1);
                    }
                    fprintf(stderr, "khdmat RIGHT_RED\n");
                    dup2(fd, STDOUT_FILENO);
                }
                else if (redir->type == APPEND)
                {
                    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    if (fd == -1)
                    {
                        fprintf(stderr, "minishell: %s: Permission denied\n", filename);
                        exit(1);
                    }
                    dup2(fd, STDOUT_FILENO);
                }
                else if (redir->type == HERDOC)
                {
                    fd = open(filename, O_RDONLY);
                    if (fd == -1)
                    {
                        fprintf(stderr, "minishell: %s: No such file or directory\n", filename);
                        exit(1);
                    }
                    dup2(fd, STDIN_FILENO);
                }
                
                if (fd != -1)
                    close(fd);
            }
            redir = redir->next; 
        }
    }
}

void create_child_processes(t_cmd **commands, int cmd_count, t_env **env, pid_t *pids)
{
    int pipe_fd[2];
    int prev_fd = -1;
    int i = 0;

    while (i < cmd_count)
    {
        if (i < cmd_count - 1 && pipe(pipe_fd) == -1)
            error_and_exit("Pipe creation failed", 1);
            
        pids[i] = fork();
        if (pids[i] == -1)
            error_and_exit("Fork failed", 1);
            
        if (pids[i] == 0)
        {
            fprintf(stderr, "commands[i]->value: %s\n", commands[i]->value);
            fprintf(stderr, "aydhkl l handel\n");
            handle_redirections(commands[i]);

            if (i > 0)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            if (i < cmd_count - 1)
            {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }

            if (commands[i]->type == COMMAND && commands[i]->value)
            {
                char **envp = ft_env_create_2d(*env);
                char **cmd_argv = ft_split(commands[i]->value, ' ');
                if (cmd_argv && cmd_argv[0])
                {
                    cmd_argv[0] = ft_strtrim(cmd_argv[0], " ");
                    fprintf(stderr ,"cmd_argv[0]: %s\n", cmd_argv[0]);
                    execute_cmd(cmd_argv, envp);
                }
                exit(127);
            }
            exit(1);
        }
        if (prev_fd != -1)
            close(prev_fd);
        if (i < cmd_count - 1)
        {
            prev_fd = pipe_fd[0];
            close(pipe_fd[1]);
        }
        i++;
    }
}
void ft_pipex(t_cmd **commands, int cmd_count, t_env **env, int *exit_status)
{
    pid_t *pids = malloc(sizeof(pid_t) * cmd_count);
    if (!pids)
        error_and_exit("Memory allocation failed", 1);

    create_child_processes(commands, cmd_count, env, pids);
    wait_for_processes(pids, cmd_count, exit_status);
    free(pids);
}
