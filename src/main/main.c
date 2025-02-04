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
#include "../../include/execution.h"
#include "../../include/parser.h"
#define MAX_TOKENS 100

char **tokenize_input(const char *input, int *num_tokens)
{
	char **tokens = malloc(MAX_TOKENS * sizeof(char *));
	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	const char *ptr = input;
	int token_count = 0;

	while (*ptr != '\0')
	{
		// Skip leading whitespace
		while (isspace((unsigned char)*ptr))
		{
			ptr++;
		}

		if (*ptr == '\0')
		{
			break;
		}

		const char *start;
		char *token;
		size_t len;

		if (*ptr == '"')
		{
			// Token is quoted
			ptr++;
			start = ptr;
			while (*ptr != '"' && *ptr != '\0')
			{
				ptr++;
			}
			len = ptr - start;
			token = malloc(len + 1);
			if (!token)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			strncpy(token, start, len);
			token[len] = '\0';
			if (*ptr == '"')
			{
				ptr++;
			}
		}
		else
		{
			// Token is unquoted
			start = ptr;
			while (!isspace((unsigned char)*ptr) && *ptr != '\0')
			{
				ptr++;
			}
			len = ptr - start;
			token = malloc(len + 1);
			if (!token)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			strncpy(token, start, len);
			token[len] = '\0';
		}

		if (token_count >= MAX_TOKENS)
		{
			fprintf(stderr, "Too many tokens\n");
			exit(EXIT_FAILURE);
		}

		tokens[token_count++] = token;
	}

	tokens[token_count] = NULL;
	*num_tokens = token_count;
	return tokens;
}
void clear_terminal(void)
{
	write(1, "\033[H\033[J", 6);
	;
}

void free_tree(t_tree *node)
{
	if (node == NULL)
		return;
	free(node->value);
	free_tree(node->left);
	free_tree(node->right);
	free(node);
}

static void ft_init(t_tool *tool, int ac, char **av, char **env)
{
	(void)(ac);
	(void)(av);
	tool->grbg = NULL;
	tool->env = ft_env_create(env);
	tool->env->a_ven = ft_env_create_2d(tool->env);
	tool->err = 0;

	// trrep->value[0] = "pwd";
	// trrep->value[1] = "env";
	// trrep->prio = 0;
	// trrep->read = 0;
	// trrep->type = 0;
	// trrep->right = NULL;
	// trrep->left = NULL;
	// execution_cmd("pwd", &tool->env, &tool->err);
}

// Function to parse tokens into an AST
t_tree *parse_tokens(char **tokens)
{
    t_tree *root = NULL;
    t_tree *current = NULL;

    for (int i = 0; tokens[i] != NULL; i++)
    {
        if (strcmp(tokens[i], "|") == 0)
        {
            t_tree *pipe_node = malloc(sizeof(t_tree));
            pipe_node->value = strdup("|");
            pipe_node->left = root;
            pipe_node->right = NULL;
            root = pipe_node;
            current = pipe_node;
        }
        else
        {
            t_tree *cmd_node = malloc(sizeof(t_tree));
            cmd_node->value = strdup(tokens[i]);
            cmd_node->left = NULL;
            cmd_node->right = NULL;
            if (current && strcmp(current->value, "|") == 0)
            {
                current->right = cmd_node;
            }
            else
            {
                root = cmd_node;
            }
        }
    }
    return root;
}
int main(int ac, char **av, char **env)
{
	t_data data;
	t_tree *tree;
	t_tool tool;
	int err;

	clear_terminal();
	signal(SIGINT, ft_sighandler);
	signal(SIGQUIT, ft_sighandler);
	ft_init(&tool, ac, av, env);
	if (!isatty(0))
		return (printf("tty required!\n"), 1);

	while (1)
	{
		data.prompt = prompt(tool.env->a_ven);

		char *input = data.prompt;
		int num_tokens;
		char **tokens = tokenize_input(input, &num_tokens);

		tree = parse_tokens(tokens);

		err = parser(&data);

		execution(tree, &tool.env, &tool.err);
	}
	return (0);
}
