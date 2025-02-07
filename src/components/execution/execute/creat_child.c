/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:54:57 by iezzam            #+#    #+#             */
/*   Updated: 2025/01/26 15:55:58 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

void redirect_fd(int from_fd, int to_fd, const char *str)
{
    if (dup2(from_fd, to_fd) == -1)
    {
        fprintf(stderr, "from_fd: %d, to_fd: %d, error: %s\n", from_fd, to_fd, str);
        error_and_exit(str, 1);
    }
    close(from_fd);
}
void child1(t_shell *data, int **wr_pipe)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        if (data->in_pipe == 1 && data->commands[0].append == 1)
        {
            redirect_fd(data->redirect->fdin, STDIN_FILENO, "dup2 failed for child1 input");
            close_fd(data->redirect);
        }
        if (data->num_cmds > 1)
            redirect_fd(wr_pipe[0][1], STDOUT_FILENO, "dup2 failed for child1 output");
        // fprintf(stderr, "child1 path: %s\n", data->commands[0].path);
        // fprintf(stderr, "child1 args: %s\n", data->commands[0].args[0]);
        // fprintf(stderr, "child1 num_cmds: %d\n", data->num_cmds);
        close_all_pipe(wr_pipe, data->num_cmds);
        // fprintf(stderr, "child11 args: %s\n", *data->commands[0].args[0]);
        fprintf(stderr, "child11 args: %s\n", *data->commands[0].args);
        execute_cmd(data->commands[0].args, data->env);
        // execve(data->commands[0].path, data->commands[0].args, data->env);
        perror("execve failed for child1");
        exit(EXIT_FAILURE);
    }
    else if (pid == -1)
    {
        close_all_pipe(wr_pipe, data->num_cmds);
        close_fd(data->redirect);
        error_and_exit("fork failed for child1", 1);
    }
}

void child2(t_shell *data, int **wr_pipe)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        redirect_fd(wr_pipe[data->num_cmds - 2][0], STDIN_FILENO, "dup2 failed for child2 input");
        if (data->commands[data->num_cmds - 1].append == 1)
        {
            redirect_fd(data->redirect->fdout, STDOUT_FILENO, "dup2 failed for child2 output");
            close_fd(data->redirect);
        }
        close_all_pipe(wr_pipe, data->num_cmds);
        execute_cmd(data->commands[data->num_cmds - 1].args, data->env);
        // execve(data->commands[data->num_cmds - 1].path, data->commands[data->num_cmds - 1].args, data->env);
        perror("execve failed for child2");
        exit(EXIT_FAILURE);
    }
    else if (pid == -1)
    {
        close_all_pipe(wr_pipe, data->num_cmds);
        close_fd(data->redirect);
        error_and_exit("fork failed for child2", 1);
    }
}

void child_intermediate(t_shell *data, int **pipes)
{
    int i = 1;
    while (i < data->num_cmds - 1)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            redirect_fd(pipes[i - 1][0], STDIN_FILENO, "dup2 failed for intermediate input");
            redirect_fd(pipes[i][1], STDOUT_FILENO, "dup2 failed for intermediate output");
            close_all_pipe(pipes, data->num_cmds);
            execute_cmd(data->commands[i].args, data->env);
            // execve(data->commands[i].path, data->commands[i].args, data->env);
            perror("execve failed for intermediate");
            exit(EXIT_FAILURE);
        }
        else if (pid == -1)
        {
            close_all_pipe(pipes, data->num_cmds);
            close_fd(data->redirect);
            error_and_exit("fork failed for intermediate", 1);
        }
        close(pipes[i - 1][0]);
        close(pipes[i - 1][1]);
        i++;
    }
}