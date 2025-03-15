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

static void execute_command(t_cmd *cmd, int input_fd, int output_fd, t_env **env)
{
    if (input_fd != STDIN_FILENO)
    {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    if (output_fd != STDOUT_FILENO)
    {
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);
    }
    execution_cmd(&cmd->value, env, NULL);
    exit(EXIT_FAILURE);
}

static void closeAll_pipe(int **pipes, int pipe_count, int keep_read, int keep_write)
{
    int i;

    i = 0;
    while (i < pipe_count)
    {
        if (i != keep_read)
            close(pipes[i][0]);
        if (i != keep_write)
            close(pipes[i][1]);
        i++;
    }
}

void child1(t_cmd *cmd, int **pipes, int pipe_count, t_env **env)
{
    
    closeAll_pipe(pipes, pipe_count, -1, 0);
    execute_command(cmd, STDIN_FILENO, pipes[0][1], env);
}

void child_last(t_cmd *cmd, int **pipes, int pipe_count, t_env **env)
{
    closeAll_pipe(pipes, pipe_count, pipe_count - 1, -1);
    execute_command(cmd, pipes[pipe_count - 1][0], STDOUT_FILENO, env);
}

void child_intermediate(t_cmd *cmd, int **pipes, int pipe_idx, int pipe_count, t_env **env)
{
    int input_fd = pipes[pipe_idx - 1][0];
    int output_fd = pipes[pipe_idx][1];

    closeAll_pipe(pipes, pipe_count, pipe_idx - 1, pipe_idx);
    execute_command(cmd, input_fd, output_fd, env);
}