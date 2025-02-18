// void handle_redirections(t_cmd **cmd)
// {
//     int fd = -1;
//     char *filename = NULL;
//     int i = 0;

//     if (cmd[i]->type != COMMAND)
//     {
//         if (cmd[i]->type == RIGHT_RED)
//         {
//             char **split_filename = ft_split(cmd[i]->next->value, ' ');
//             if (!split_filename || !split_filename[0])
//             {
//                 fprintf(stderr, "minishell: invalid redirection\n");
//                 exit(1);
//             }
//             filename = clean_filename(split_filename[0]);
//             if (cmd[i]->next->type == FILENAME)
//             {
//                 fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
//                 if (fd == -1)
//                 {
//                     fprintf(stderr, "Not creat: %s\n", filename);
//                     exit(1);
//                 }
//                 fprintf(stderr, "creat fille: %s\n", filename);
//                 dup2(fd, STDOUT_FILENO);
//                 close(fd);
//             }
//         }
//     }
//     else
//         fprintf(stderr, "cmd[i]->type == COOMAND %s\n", cmd[i]->value);
// }


// void handle_redirections(t_cmd *cmd)
// {
//     int fd;
//     char *filename;

//     while (cmd)
//     {
//         fprintf(stderr, "2cmd->value: %s\n", cmd->value);
//         if (cmd->type == RIGHT_RED)
//         {
//             fprintf(stderr, "RIGHT_RED\n");
//             if (!cmd->next || cmd->next->type != FILENAME)
//             {
//                 fprintf(stderr, "minishell: syntax error near unexpected token `newline`\n");
//                 exit(1);
//             }
//             filename = clean_filename(cmd->next->value);
//             if (!filename || !*filename)
//             {
//                 fprintf(stderr, "minishell: invalid filename\n");
//                 exit(1);
//             }

//             fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//             if (fd == -1)
//             {
//                 perror("minishell");
//                 exit(1);
//             }

//             close(STDOUT_FILENO);

//             if (dup2(fd, STDOUT_FILENO) == -1)
//             {
//                 perror("dup2 failed");
//                 close(fd);
//                 exit(1);
//             }
//             close(fd);
//             return;
//         }
//         cmd = cmd->next;
//     }
// }



// void handle_redirections(t_cmd *cmd)
// {
//     t_cmd *redir = cmd;
//     int fd = -1;
//     char *filename = NULL;
//     static int i = 0;
//     if (cmd->type != COMMAND)
//     {
//         while (redir && (redir->type == LEFT_RED || redir->type == RIGHT_RED ||
//                 redir->type == APPEND || redir->type == HERDOC))
//         {
//             fprintf(stderr, "i: %d\n", i++);
//             fprintf(stderr ,"redir->value: %s\n", redir->value);
//             if (redir->next && redir->next->value)
//             {
//                 char **split_filename = ft_split(redir->next->value, ' ');
//                 if (!split_filename || !split_filename[0])
//                 {
//                     fprintf(stderr, "minishell: invalid redirection\n");
//                     exit(1);
//                 }

//                 filename = clean_filename(split_filename[0]);
//                 fprintf(stderr, "filename: %s\n", filename);
//                 if (redir->type == LEFT_RED)
//                 {
//                     fd = open(filename, O_RDONLY);
//                     if (fd == -1)
//                     {
//                         fprintf(stderr, "minishell: %s: No such file or directory\n", filename);
//                         exit(1);
//                     }
//                     dup2(fd, STDIN_FILENO);
//                 }
//                 else if (redir->type == RIGHT_RED)
//                 {
//                     fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
//                     if (fd == -1)
//                     {
//                         fprintf(stderr, "minishell: %s: Permission denied\n", filename);
//                         exit(1);
//                     }
//                     fprintf(stderr, "khdmat RIGHT_RED\n");
//                     dup2(fd, STDOUT_FILENO);
//                 }
//                 else if (redir->type == APPEND)
//                 {
//                     fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
//                     if (fd == -1)
//                     {
//                         fprintf(stderr, "minishell: %s: Permission denied\n", filename);
//                         exit(1);
//                     }
//                     dup2(fd, STDOUT_FILENO);
//                 }
//                 else if (redir->type == HERDOC)
//                 {
//                     fd = open(filename, O_RDONLY);
//                     if (fd == -1)
//                     {
//                         fprintf(stderr, "minishell: %s: No such file or directory\n", filename);
//                         exit(1);
//                     }
//                     dup2(fd, STDIN_FILENO);
//                 }

//                 if (fd != -1)
//                     close(fd);
//             }
//             redir = redir->next;
//         }
//     }
// }

