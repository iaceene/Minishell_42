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

static void close_pipes(int **pipes, int count)
{
  int i;

  i = 0;
  while (i < count)
  {
    close(pipes[i][0]);
    close(pipes[i][1]);
    i++;
  }
}

static void free_pipes(int **pipes, int count)
{
  int i;

  i = 0;
  while (i < count)
    free(pipes[i++]);
  free(pipes);
}

static int **create_pipes(int count)
{
  int i;
  int **pipes;

  i = 0;
  pipes = ft_malloc(sizeof(int *) * count);
  while (i < count)
  {
    pipes[i] = ft_malloc(sizeof(int) * 2);
    if (!pipes[i])
    {
      free_pipes(pipes, i);
      return NULL;
    }
    if (pipe(pipes[i]) == -1)
    {
      free_pipes(pipes, i);
      return NULL;
    }
    i++;
  }
  return pipes;
}
void create_child_processes(t_cmd **commands, int cmd_count, int **pipes, int pipe_count, t_env **env, pid_t *pids)
{
  int i;

  i = 0;
  while (i < cmd_count)
  {
    pids[i] = fork();
    if (pids[i] == -1)
    {
      close_pipes(pipes, pipe_count);
      free_pipes(pipes, pipe_count);
      free(pids);
      error_and_exit("Fork failed", 1);
    }
    if (pids[i] == 0)
    {
      if (i == 0)
        child1(commands[i], pipes, pipe_count, env);
      else if (i == cmd_count - 1)
        child_last(commands[i], pipes, pipe_count, env);
      else
        child_intermediate(commands[i], pipes, i, pipe_count, env);
    }
  }
  i++;
}

void wait_for_processes(pid_t *pids, int cmd_count, int *exit_status)
{
  int last_status;
  int i;

  i = 0;
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
void ft_pipex(t_cmd **commands, int cmd_count, t_env **env, int *exit_status)
{
  int pipe_count;
  int **pipes;
  pid_t *pids;

  pipe_count = cmd_count - 1;
  pipes = create_pipes(pipe_count);
  if (!pipes)
    error_and_exit("Pipe creation failed", 1);
  pids = ft_malloc(sizeof(pid_t) * cmd_count);
  if (!pids)
  {
    free_pipes(pipes, pipe_count);
    error_and_exit("Memory allocation failed", 1);
  }
  create_child_processes(commands, cmd_count, pipes, pipe_count, env, pids);
  close_pipes(pipes, pipe_count);
  free_pipes(pipes, pipe_count);
  wait_for_processes(pids, cmd_count, exit_status);
  free(pids);
}