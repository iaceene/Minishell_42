/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:58:16 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/03 05:51:34 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
#define PARSER_H

#include "minishell.h"

typedef enum {
	WORD,       // Command or argument
	PIPE,       // |
	RIGHT_APP,		// >>
	LEFT_APP,		// <<
	RIGHT_RED,	// >
	LEFT_RED,	// <
	AND,        // &&
	OR,         // ||
	SIN_QUOTE,  // '
	DOB_QUOTE, // "
	DOLLAR,     // $
	OPEN_PAR,  // (
	CLOSE_PAR, // )
	TOKEN_EOF         // End of input
} TokenType;

typedef struct s_node{
	TokenType			type;   // Type of token
	char				*value;
	int					flaged;
	struct  s_node		*next;
} t_node;

typedef struct s_cmd
{
	TokenType	type;
	char		*value;
	struct s_cmd *left;
	struct s_cmd *right;
}t_cmd;


t_node	*lexer_init(const char *str);
int		syntax_checker(t_node *data);
char	**ft_split_word(char *str, char *word);
void	add_to_list(t_node **head, t_node *new);
t_node	*add_new_node(TokenType type, char *val);
int		ft_isalnum(char c);
char	*extract_word(char *s);

#endif