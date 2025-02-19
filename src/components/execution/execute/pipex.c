/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*   Created: 2025/01/25 10:13:16 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/26 15:43:13 by iezzam           ###   ########.fr       */
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
            if (cmd->type == INFILE || cmd->type == HEREDOC_FILE)
            {
                if (*infile != -1)
                    close(*infile);
                *infile = open(filename, O_RDONLY);
                if (*infile < 0)
                    perror("Failed to open input file");
            }
            else if (cmd->type == OUTFILE)
            {
                if (*outfile != -1)
                    close(*outfile);
                *outfile = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
                if (*outfile < 0)
                    error_and_exit("Failed to open output file", 1);
            }
            else if (cmd->type == APPEND_FILE)
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

void execute_command(t_exec *cmd, char **env, int in_fd, int out_fd)
{
    if (in_fd != -1)
        redirect_fd(in_fd, STDIN_FILENO, "dup2 failed (stdin)");
    if (out_fd != -1)
        redirect_fd(out_fd, STDOUT_FILENO, "dup2 failed (stdout)");

    char **cmd_args = ft_split(cmd->value, ' ');
    if (!cmd_args)
        error_and_exit("Failed to split command", 1);
    execute_cmd(cmd_args, env);
}

void	ft_pipex(t_exec *commands, int cmd_counxt, t_env **env, int *exit_status)
{
    (void)cmd_counxt;
    int infile = -1, outfile = -1;
    int pipe_fd[2];
    int prev_pipe_read = -1;
    pid_t pid;
    char **envp = ft_env_create_2d(*env);
    int cmd_count = count_commands(commands);
    int current_cmd = 0;

    handle_file_redirection(commands, &infile, &outfile);

    // Process commands
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
            {
                if (current_cmd == 0)
                {
                    if (infile != -1)
                        redirect_fd(infile, STDIN_FILENO, "dup2 failed (stdin)");
                }
                else
                {
                    redirect_fd(prev_pipe_read, STDIN_FILENO, "dup2 failed (stdin)");
                }

                if (current_cmd == cmd_count - 1)
                {
                    if (outfile != -1)
                        redirect_fd(outfile, STDOUT_FILENO, "dup2 failed (stdout)");
                }
                else
                {
                    redirect_fd(pipe_fd[1], STDOUT_FILENO, "dup2 failed (stdout)");
                }

                execute_command(cmd, envp, -1, -1);
                exit(1);
            }
            else if (pid < 0)
            {
                error_and_exit("Fork failed", 1);
            }

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
    for (int i = 0; i < cmd_count; i++)
    {
        wait(&status);
        if (WIFEXITED(status))
            last_status = WEXITSTATUS(status);
    }
    *exit_status = last_status;
}