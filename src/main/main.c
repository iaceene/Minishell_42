/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:48:34 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/31 18:42:28 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_terminal(void)
{
	write(1, "\033[H\033[J", 6);
}

char    *get_next_line(int fd) 
{
        static char     buffer[BUFFER_SIZE];
        static char            line[100000];
        static int      buffer_pos;
        static int      reads_size;
        int             i;

        i = 0;
        if (fd < 0 || BUFFER_SIZE <= 0)
                return NULL;
        while (1337)
        {
                if (buffer_pos >= reads_size)
                {   
                        reads_size = read(fd, buffer, BUFFER_SIZE);
                        buffer_pos = 0;
                        if (reads_size <= 0)
                                break ;
                }
                line[i++] = buffer[buffer_pos++];
                if (buffer[buffer_pos - 1] == '\n' || i >= (int)sizeof(line) - 1)
                        break ;
        }
        line[i] = 0;
        if (i == 0)
                return NULL;
        return (ft_strdup(line));
}

char	*get_cnt(int fd)
{
	if (fd == -1)
		return (ft_strdup("fail to open\n"));
	char *tmp;
	char *buff = NULL;
	tmp = get_next_line(fd);
	while (tmp)
	{
		buff = ft_strjoin(buff, tmp);
		tmp = get_next_line(fd);
	}
	return (buff);
}

static void	ft_init(t_tool *tool, char **env, t_data *data)
{
	tool->env = ft_env_create(env);
	data->final_env = tool->env;
	tool->env->a_ven = ft_env_create_2d(tool->env);
	data->exe_state = 0;
}

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

// Function to print command arguments
void printing(char **v)
{
    int i = 0;

    if (!v)
        return ;

    while (v[i])
    {
        if (i == 0)
            printf(GREEN "[" RESET "%s" GREEN "] " RESET, v[i]);
        else
            printf(YELLOW "ARG [" RESET "%s" YELLOW "] " RESET, v[i]);
        i++;
    }
    printf("\n");
}

// Function to print final data with formatting
void print_final_data(t_cmd *head)
{
    while (head)
    {
        if (head->type == COMMAND)
		{
            printf(CYAN "COMMAND" RESET " --> ");
        	printing(head->cmd);
		}
        else if (head->type == IN_FILE)
            printf(MAGENTA "INFILE [" RESET "%s" MAGENTA "]\n" RESET, head->value);
        else if (head->type == OUT_FILE)
            printf(MAGENTA "OUTFILE [" RESET "%s" MAGENTA "]\n" RESET, head->value);
        else if (head->type == APPEND)
            printf(MAGENTA "APPEND [" RESET "%s" MAGENTA "]\n" RESET, head->value);
        else if (head->type == HERDOC)
            printf(MAGENTA "HERDOC fd [" RESET "%d" MAGENTA "] content [" RESET "%s" MAGENTA "]\n" RESET, head->fd_herdoc, get_cnt(head->fd_herdoc));
        else if (head->value)
            printf(BLUE "%s\n" RESET, head->value);
		if (head->type == COMMAND && head->next && head->next->type == COMMAND)
            printf(BLUE "%s\n" RESET, "PIPED TO");
        head = head->next;
    }
    printf(""RESET);

}



int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_tool	tool;

	clear_terminal();
	data.env = env;
	signal(SIGINT, ft_sighandler);
	signal(SIGQUIT, ft_sighandler);
	ft_init(&tool, env, &data);
	data.final_env->data = &data;
	while (1)
	{
		data.prompt = prompt(env);
		if (!data.prompt[0])
			ft_puterr(32);
		else if (parser(&data))
		{
			print_final_data(data.head);
			// execution(&data.head, &tool.env, &data.exe_state);
			// print_final_data(data.head, &data.exe_state);
		}
		else
			ft_puterr(14);
	}
	(void)ac;
	(void)av;
	return (0);
}
