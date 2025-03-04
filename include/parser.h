/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:48:43 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/04 17:35:55 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

# include "minishell.h"
# include "stdbool.h"


typedef struct s_node{
	TokenType			type;   // Type of token
	char				*value;
	bool			    visit;
	struct  s_node		*next;
} t_node;

typedef enum {
    STATE_NORMAL,
    STATE_IN_SINGLE_QUOTE,
    STATE_IN_DOUBLE_QUOTE
} ParserState;

t_node	*lexer_init(const char *str);
int		check_no_opned_pr(t_node *data);
int		find_it(char *s, char c);
int		check_qoats(char *val);
int		others_checker(t_node *data);
int		check_redirction(t_node *data);
int		valid_next(TokenType type);
int		check_append(t_node *data);
int		ft_isascii(int c);
char	*ft_strndup(char *s, size_t n);
int		operator(char c);
char	*find_dollar(char *s);
int		syntax_checker(t_node *data);
char	**ft_split_word(char *str, char *word);
void	add_to_list(t_node **head, t_node *new);
t_node	*add_new_node(TokenType type, char *val);
int		ft_isalnum(char c);
char	*extract_word(char *s);
void    add_to_cmd(t_cmd **head, t_cmd *new);
t_cmd   *new_cmd(t_node *node);
char	*expander(t_node *node, t_env *head);
char	*expand_one_arg(char *s, t_env *head);
char	*multiple_var_expander(char *s, t_env *head);
t_cmd	*data_maker(t_node *head, t_env *env);


#endif