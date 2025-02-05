/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:58:16 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/05 19:57:02 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
#define PARSER_H

#include "minishell.h"

typedef enum {
	COMMAND,       // Command or argument
	PIPE,       // |
	APPEND,		// >>
	HERDOC,		// <<
	RIGHT_RED,	// >
	LEFT_RED,	// <
	SIN_QUOTE,  // '
	DOB_QUOTE, // "
	DOLLAR,     // $
	OPEN_PAR,  // (
	CLOSE_PAR, // )
} TokenType;

typedef struct s_node{
	TokenType			type;   // Type of token
	char				*value;
	int					flaged;
	int					visit;
	struct  s_node		*next;
} t_node;


// struct 
typedef struct s_cmd
{
	TokenType		type;
	char			*value;
	char 			**args;
	struct s_cmd	*next;
}	t_cmd;

t_node	*lexer_init(const char *str);
int		ft_isascii(int c);
int		operator(char c);
int		syntax_checker(t_node *data);
char	**ft_split_word(char *str, char *word);
void	add_to_list(t_node **head, t_node *new);
t_node	*add_new_node(TokenType type, char *val);
int		ft_isalnum(char c);
char	*extract_word(char *s);
void print_data(t_node *data);

#endif