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

#include "../../../include/minishell.h"

// void exec_ast(t_ast *node)
// {
//   if (!node)
//     return;

//   // else if (strcmp(node->type, "HEREDOC") == 0)
//   // {
//   //   handle_heredoc(node);
//   // }
//   if (ft_strcmp(node->type, "PIPE") == 0)
//   {
//     ft_pipex(node);
//   }
//   else if (strcmp(node->type, "CMD") == 0)
//   {
//     exec_command(node);
//   }
//   else if (strcmp(node->type, "REDIR") == 0)
//   {
//     exec_redir(node);
//   }
// }

void execution(t_shell *shell)
{
    ft_pipex(shell);
}