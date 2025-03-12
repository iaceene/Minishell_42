/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:02:23 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/19 10:02:23 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

void close_all_pipe(int **pipes, int num_cmd)
{
    int j;

    if (!pipes)
        return;
    j = 0;
    while (j < num_cmd - 1)
    {
        close(pipes[j][0]);
        close(pipes[j][1]);
        j++;
    }
}

void free_all_pipe(int **pipes, int i)
{
    while (--i >= 0)
        free(pipes[i]);
    free(pipes);
}

void redirect_fd(int from_fd, int to_fd, const char *error_msg)
{
    if (from_fd < 0 || to_fd < 0)
        error_and_exit((char *)error_msg, 1);
    if (dup2(from_fd, to_fd) == -1)
        error_and_exit((char *)error_msg, 1);
    close(from_fd);
}

char *clean_filename(char *filename)
{
    if (!filename)
        return NULL;
    while (*filename == ' ')
        filename++;
    int len = ft_strlen(filename);
    while (len > 0 && filename[len - 1] == ' ')
        filename[--len] = '\0';
    if (filename[0] == '\'' || filename[0] == '"')
        ft_memmove(filename, filename + 1, ft_strlen(filename));
    len = ft_strlen(filename);
    if (len > 0 && (filename[len - 1] == '\'' || filename[len - 1] == '"'))
        filename[len - 1] = '\0';
    return filename;
}

void handle_file_redirection(t_exec *cmd, int *infile, int *outfile)
{
    char *filename;

    while (cmd)
    {
        if (cmd->type != COMMAND)
        {
            filename = clean_filename(cmd->value);
            if (cmd->type == IN_FILE)
            {
                if (*infile != -1)
                    close(*infile);
                *infile = open(filename, O_RDONLY);
                if (*infile < 0)
                {
                    write(2, "Failed to open input file: ", 27);
                    write(2, filename, ft_strlen(filename));
                    write(2, "\n", 1);
                }
            }
            else if (cmd->type == OUT_FILE)
            {
                if (*outfile != -1)
                    close(*outfile);
                *outfile = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
                if (*outfile < 0)
                    error_and_exit("Failed to open output file", 1);
            }
            else if (cmd->type == APPEND)
            {
                if (*outfile != -1)
                    close(*outfile);
                *outfile = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
                if (*outfile < 0)
                    error_and_exit("Failed to open output file for append", 1);
            }
        }
        cmd = cmd->next;
    }
}

int count_commands(t_exec *cmd)
{
    int count = 0;
    while (cmd)
    {
        if (cmd->type == COMMAND)
            count++;
        cmd = cmd->next;
    }
    return count;
}

void cleanup_child_fds(int infile, int outfile, int pipe_read, int pipe_write, int prev_pipe)
{
    if (infile != -1 && infile != STDIN_FILENO)
        close(infile);
    if (outfile != -1 && outfile != STDOUT_FILENO)
        close(outfile);
    if (pipe_read != -1 && pipe_read != STDIN_FILENO)
        close(pipe_read);
    if (pipe_write != -1 && pipe_write != STDOUT_FILENO)
        close(pipe_write);
    if (prev_pipe != -1 && prev_pipe != STDIN_FILENO)
        close(prev_pipe);
}

void execute_command(t_exec *cmd, char **env)
{
    char **cmd_args = ft_split(cmd->value, ' ');
    if (!cmd_args)
        error_and_exit("Failed to split command", 1);
    execute_cmd(cmd_args, env);
}

void handle_child_process(t_exec *cmd, char **env, int infile, int outfile,
                          int *pipe_fd, int prev_pipe_read, int current_cmd, int cmd_count)
{
    if (current_cmd == 0 && infile != -1)
        redirect_fd(infile, STDIN_FILENO, "dup2 failed (stdin)");
    else if (current_cmd > 0)
        redirect_fd(prev_pipe_read, STDIN_FILENO, "dup2 failed (stdin)");
    if (current_cmd == cmd_count - 1 && outfile != -1)
        redirect_fd(outfile, STDOUT_FILENO, "dup2 failed (stdout)");
    else if (current_cmd < cmd_count - 1)
        redirect_fd(pipe_fd[1], STDOUT_FILENO, "dup2 failed (stdout)");
    cleanup_child_fds(infile, outfile, pipe_fd[0], pipe_fd[1], prev_pipe_read);
    execute_command(cmd, env);
    exit(1);
}

void ft_pipex(t_exec *commands, t_env **env, int *exit_status)
{
    int infile = -1, outfile = -1;
    int pipe_fd[2] = {-1, -1};
    int prev_pipe_read = -1;
    pid_t pid;
    char **envp = ft_env_create_2d(*env);
    int cmd_count = count_commands(commands);
    int current_cmd = 0;

    handle_file_redirection(commands, &infile, &outfile);
    t_exec *cmd = commands;
    while (cmd)
    {
        if (cmd->type == COMMAND)
        {
            if (current_cmd < cmd_count - 1)
            {
                if (pipe(pipe_fd) == -1)
                    error_and_exit("Pipe creation failed", 1);
            }
            pid = fork();
            if (pid == 0)
                handle_child_process(cmd, envp, infile, outfile,
                                    pipe_fd, prev_pipe_read, current_cmd, cmd_count);
            else if (pid < 0)
                error_and_exit("Fork failed", 1);
            if (prev_pipe_read != -1)
                close(prev_pipe_read);
            if (current_cmd < cmd_count - 1)
            {
                close(pipe_fd[1]);
                prev_pipe_read = pipe_fd[0];
            }
            current_cmd++;
        }
        cmd = cmd->next;
    }
    if (infile != -1)
        close(infile);
    if (outfile != -1)
        close(outfile);
    if (prev_pipe_read != -1)
        close(prev_pipe_read);
    int status;
    int last_status = 0;
    int i = 0;
    while (i < cmd_count)
    {
        wait(&status);
        if (WIFEXITED(status))
            last_status = WEXITSTATUS(status);
        i++;
    }
    *exit_status = last_status;
}
