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

int creat_file(t_cmd *cmd)
{
    int i = 0;
    while (cmd)
    {
        printf("cmd->value: %s\n", cmd->value);
        i++;
    }
    return 0;
}
void open_file(t_exec *cmd, int *infile, int *outfile)
{
    char *filename = clean_filename(cmd->value);
    if (cmd->type == INFILE || cmd->type == HEREDOC_FILE)
    {
        *infile = open(filename, O_RDONLY);
        if (*infile < 0)
            perror("Failed to open input file");
    }
    else if (cmd->type == OUTFILE)
    {
        *outfile = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (*outfile < 0)
            error_and_exit("Failed to open output file", 1);
    }
    else if (cmd->type == APPEND_FILE)
    {
        *outfile = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
        if (*outfile < 0)
            error_and_exit("Failed to open output file for append", 1);
    }
}

void setup_redirections(int i, int num_cmds, int infile, int outfile, int **pipes)
{
    if (i == 0)
    {
        if (infile != -1)
            redirect_fd(infile, STDIN_FILENO, "dup2 failed (stdin)");
        if (num_cmds > 1)
            redirect_fd(pipes[i][1], STDOUT_FILENO, "dup2 failed (stdout)");
    }
    else if (i == num_cmds - 1)
    {
        if (outfile != -1)
            redirect_fd(outfile, STDOUT_FILENO, "dup2 failed (stdout)");
        redirect_fd(pipes[i - 1][0], STDIN_FILENO, "dup2 failed (stdin)");
    }
    else
    {
        redirect_fd(pipes[i - 1][0], STDIN_FILENO, "dup2 failed (stdin)");
        redirect_fd(pipes[i][1], STDOUT_FILENO, "dup2 failed (stdout)");
    }
}

void execute_child_command(t_exec *cmd, char **env)
{
    if (cmd->value && cmd->type == COMMAND)
    {
        fprintf(stderr, "cmd->value in child_process: %s\n", cmd->value);
        char **cmd_args = ft_split(cmd->value, ' ');
        if (!cmd_args)
            error_and_exit("Failed to split command", 1);
        execute_cmd(cmd_args, env);
    }
}

void child_process(t_exec *cmd, int **pipes, char **env, int i, int num_cmds)
{
    int infile = -1, outfile = -1;
    open_file(cmd, &infile, &outfile);
    setup_redirections(i, num_cmds, infile, outfile, pipes);
    close_all_pipe(pipes, num_cmds);
    execute_child_command(cmd, env);
}

void fork_child_processes(t_exec *commands, int **pipes, char **env, int num_cmds)
{

    pid_t pid;
    int i = 0;
    t_exec *cmd = commands;

    while (cmd && i < num_cmds)
    {
        fprintf(stderr, "cmd->value: %s\n", cmd->value);
        
        pid = fork();
        if (pid == 0)
            child_process(cmd, pipes, env, i, num_cmds);
        else if (pid < 0)
        {
            perror("fork failed");
            close_all_pipe(pipes, num_cmds);
            free_all_pipe(pipes, num_cmds - 1);
            exit(1);
        }
        cmd = cmd->next;
        i++;
    }
}

void wait_for_processes(int num_cmds, int *exit_status)
{
    int status;
    int last_status = 0;

    int i = 0;
    while (i < num_cmds)
    {
        wait(&status);
        if (WIFEXITED(status))
            last_status = WEXITSTATUS(status);
        i++;
    }
    *exit_status = last_status;
}

void ft_pipex(t_exec *commands, int cmd_count, t_env **env, int *exit_status)
{
    int **pipes = calloc(cmd_count - 1, sizeof(int *));
    if (!pipes)
        error_and_exit("Pipe allocation failed", 1);

    int i = 0;
    while (i < cmd_count - 1)
    {
        pipes[i] = ft_malloc(2 * sizeof(int));
        if (!pipes[i] || pipe(pipes[i]) == -1)
        {
            free_all_pipe(pipes, i);
            error_and_exit("Pipe creation failed", 1);
        }
        i++;
    }

    char **envp = ft_env_create_2d(*env);

    fork_child_processes(commands, pipes, envp, cmd_count);

    close_all_pipe(pipes, cmd_count);
    free_all_pipe(pipes, cmd_count - 1);
    wait_for_processes(cmd_count, exit_status);
}
