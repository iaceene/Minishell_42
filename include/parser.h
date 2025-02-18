/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:48:43 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/15 11:24:19 by iezzam           ###   ########.fr       */
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
char	*expander(char *node, t_fake_env *head);
char	*expand_one_arg(char *s, t_fake_env *head);
char	*multiple_var_expander(char *s, t_fake_env *head);
t_cmd	*data_maker(t_node *head, t_fake_env *env);
int		there_is_qoats(char *s);
int		ft_find(char *s, char c);
void	command_handler(t_node *node, t_fake_env *env);

void print_data(t_node *data);

#endif