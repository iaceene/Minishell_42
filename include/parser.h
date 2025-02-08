/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:48:43 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/08 09:23:13 by iezzam           ###   ########.fr       */
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

typedef struct s_fake_env
{
    char                *key;
    char                *value;
    struct s_fake_env   *next;
}t_fake_env;


t_node	*lexer_init(const char *str);
int		ft_isascii(int c);
int		operator(char c);
int		syntax_checker(t_node *data);
char	**ft_split_word(char *str, char *word);
void	add_to_list(t_node **head, t_node *new);
t_node	*add_new_node(TokenType type, char *val);
int		ft_isalnum(char c);
char	*extract_word(char *s);
void    add_to_cmd(t_cmd **head, t_cmd *new);
t_cmd   *new_cmd(t_node *node);
void	expander(t_node *node, t_fake_env *head, t_cmd **cmd);
t_cmd	*data_maker(t_node *head, t_fake_env *env);
void print_data(t_node *data);

#endif