/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:58:16 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/03 03:01:58 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
#define PARSER_H

#include "minishell.h"

typedef enum {
	TOKEN_WORD,       // Command or argument
	TOKEN_PIPE,       // |
	TOKEN_REDIRECT,   // >, <, >>, <<
	TOKEN_AND,        // &&
	TOKEN_OR,         // ||
	TOKEN_QUOTE,      // ' or "
	TOKEN_DOLLAR,     // $
	TOKEN_EOF         // End of input
} TokenType;

typedef struct s_node{
	TokenType			type;   // Type of token
	char				*value;
	struct  s_node		*next;
} t_node;

int		lexer_init(char *str);
char	**ft_split_word(char *str, char *word);
void	add_to_list(t_node **head, t_node *new);
t_node	*add_new_node(TokenType type, char *val);
int		ft_isspace(char c);
int		ft_isalnum(char c);

#endif