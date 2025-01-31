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

#include "../../../include/minishell.h"

void close_fd(t_redirect *data)
{
  close(data->fdin);
  close(data->fdout);
}

void close_all_pipe(int **pipes, int num_cmd)
{
  int j;

  j = 0;
  if (!pipes)
    return;
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

int **allocate_pipes(int num_pipes)
{
  int **pipes = malloc(num_pipes * sizeof(int *));
  if (!pipes)
    return NULL;
  int i = 0;
  while (i < num_pipes)
  {
    pipes[i] = malloc(2 * sizeof(int));
    if (!pipes[i] || pipe(pipes[i]) == -1)
    {
      free_all_pipe(pipes, i);
      error_and_exit("Failed to create pipe\n", 1);
    }
    i++;
  }
  return pipes;
}

void ft_pipex(t_shell *shell)
{
  int **pipes;
  int num_cmds = shell->num_cmds;

  pipes = allocate_pipes(num_cmds - 1);
  if (!pipes)
    error_and_exit("Failed to allocate pipes\n", 1);


  child1(shell, pipes);

  if (num_cmds > 2)
    child_intermediate(shell, pipes);

  if (num_cmds > 1)
    child2(shell, pipes);

  close_all_pipe(pipes, num_cmds);
  if (shell->redirect->fdin != STDIN_FILENO)
    close_fd(shell->redirect);
  free_all_pipe(pipes, num_cmds - 1);

  int i = 0;
  while (i < num_cmds)
  {
    int status;
    wait(&status);
    if (WIFEXITED(status))
      shell->last_exit = WEXITSTATUS(status);
    i++;
  }
  fprintf(stderr, "last exit: %d\n", shell->last_exit);
}

// void ft_pipex(t_ast *node)
// {
//     int **pipes;
//     int num_cmds;
//     t_ast *curr_node = node;
//     t_shell shell;

//     num_cmds = 0;
//     while (curr_node)
//     {
//         num_cmds++;
//         curr_node = curr_node->right;
//     }
//     shell.num_cmds = num_cmds;

//     pipes = allocate_pipes(num_cmds - 1);
//     if (!pipes)
//         error_and_exit("Failed to allocate pipes\n", 1);

//     child1(&shell, pipes);

//     if (num_cmds > 2)
//         child_intermediate(&shell, pipes);

//     if (num_cmds > 1)
//         child2(&shell, pipes);

//     close_all_pipe(pipes, num_cmds);
//     if (shell.redirect->fdin != STDIN_FILENO)
//         close_fd(shell.redirect);

//     free_all_pipe(pipes, num_cmds - 1);

//     int i = 0;
//     while (i < num_cmds)
//     {
//         int status;
//         wait(&status);
//         if (WIFEXITED(status))
//             shell.last_exit = WEXITSTATUS(status);
//         i++;
//     }
//     fprintf(stderr, "last exit: %d\n", shell.last_exit);
// }
