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
    int i = 0;
    int last_status = 0;
    while (i < cmd_count)
    {
        int status;
        waitpid(pids[i], &status, 0);
        if (i == cmd_count - 1)
            last_status = status;
        i++;
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

void save_std_fds(int *saved_stdout, int *saved_stdin)
{
    *saved_stdout = dup(STDOUT_FILENO);
    *saved_stdin = dup(STDIN_FILENO);
    if (*saved_stdout == -1 || *saved_stdin == -1)
    {
        perror("dup failed");
        exit(1);
    }
}

void restore_std_fds(int saved_stdout, int saved_stdin)
{
    if (dup2(saved_stdout, STDOUT_FILENO) == -1 ||
        dup2(saved_stdin, STDIN_FILENO) == -1)
    {
        perror("dup2 failed");
        exit(1);
    }
    close(saved_stdout);
    close(saved_stdin);
}

void handle_redirections(t_exec *cmd)
{
    fprintf(stderr, "handeling redirections\n");
    int fd;
    char *filename;
    int saved_stdout, saved_stdin;

    fd = -1;
    if (!cmd)
        return;
    // if (!cmd->type || !cmd->value)
    //     return;

    save_std_fds(&saved_stdout, &saved_stdin);
    filename = cmd->value;
    // filename = clean_filename(cmd->value);
    if (!filename || !*filename)
    {
        fprintf(stderr, "minishell: invalid filename\n");
        exit(1);
    }
    fprintf(stderr ,"filename: %s\n", filename);
    if (cmd->type == INFILE)
    {
        fd = open(filename, O_RDONLY);
        if (fd == -1)
        {
            perror("minishell: input");
            exit(1);
        }
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("dup2 failed");
            close(fd);
            exit(1);
        }
    }
    else if (cmd->type == OUTFILE)
    {
        fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror("minishell: output");
            exit(1);
        }
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            perror("dup2 failed");
            fprintf(stderr ,"OUTFILE fd: %d\n", fd);
            close(fd);
            return ;
            // exit(1);
        }
    }
    else if (cmd->type == APPEND_FILE)
    {
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            perror("minishell: append");
            exit(1);
        }
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            perror("dup2 failed");
            close(fd);
            exit(1);
        }
    }
    else if (cmd->type == HEREDOC_FILE)
    {
        fd = atoi(filename);
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("dup2 failed");
            close(fd);
            exit(1);
        }
    }
    close(fd);
}

void create_child_processes(t_exec *commands, int cmd_count, t_env **env, pid_t *pids)
{
    int pipe_fd[2];
    int prev_fd = -1;
    int i = 0;
    t_exec *current = commands;

    while (i < cmd_count)
    {
        if (i < cmd_count - 1)
        {
            if (pipe(pipe_fd) == -1)
                error_and_exit("Pipe creation failed", 1);
        }

        pids[i] = fork();
        if (pids[i] == -1)
            error_and_exit("Fork failed", 1);

                handle_redirections(current);
        if (pids[i] == 0)
        {
            if (i > 0)
            {
                if (dup2(prev_fd, STDIN_FILENO) == -1)
                    error_and_exit("dup2 failed", 1);
                close(prev_fd);
            }

            if (i < cmd_count - 1)
            {
                if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
                    error_and_exit("dup2 failed", 1);
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }

            // t_exec *temp = current;
            // while (temp)
            // {
                // temp = temp->next;
            // }

            if (current->type == COMMAND && current->value)
            {
                char **envp = ft_env_create_2d(*env);
                char **cmd_argv = ft_split(current->value, ' ');
                if (cmd_argv && cmd_argv[0])
                {
                    cmd_argv[0] = ft_strtrim(cmd_argv[0], " ");
                    execute_cmd(cmd_argv, envp);
                }
            }
            exit(127);
        }

        if (prev_fd != -1)
            close(prev_fd);
        if (i < cmd_count - 1)
        {
            prev_fd = pipe_fd[0];
            close(pipe_fd[1]);
        }

        while (current && current->next && current->next->type != COMMAND)
            current = current->next;
        if (current)
            current = current->next;
        i++;
    }
}

void ft_pipex(t_exec *commands, int cmd_count, t_env **env, int *exit_status)
{
    pid_t *pids;

    pids = malloc(sizeof(pid_t) * cmd_count);
    if (!pids)
        error_and_exit("Memory allocation failed", 1);

    create_child_processes(commands, cmd_count, env, pids);
    wait_for_processes(pids, cmd_count, exit_status);
    free(pids);
}

// cat | cat | cat | cat | cat | ls -la > l7wa.txt > l7wa.txt file1.txt > file2.txt > file3.txt