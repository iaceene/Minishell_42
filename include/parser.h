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

typedef struct s_node{
	TokenType			type;   // Type of token
	char				*value;
	int					flaged;
	struct  s_node		*next;
} t_node;


t_node	*lexer_init(const char *str);
int		ft_isascii(int c);
int		operator(char c);
int		syntax_checker(t_node *data);
char	**ft_split_word(char *str, char *word);
void	add_to_list(t_node **head, t_node *new);
t_node	*add_new_node(TokenType type, char *val);
int		ft_isalnum(char c);
char	*extract_word(char *s);
t_cmd	*data_maker(t_node *head);
void print_data(t_node *data);

#endif