/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:48:43 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/07 21:00:20 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

# include "minishell.h"
# include "stdbool.h"

typedef struct s_node{
	TokenType			type;
	char				*value;
	bool			    visit;
	struct  s_node		*next;
} t_node;

typedef enum {
    NORMAL,
    IN_SQUOTE,
    IN_DQUOTE
} State;

typedef struct s_expand
{
	State			state;
	char			*val;
	struct s_expand	*next;
}	t_expand;

t_node		*lexer_init(const char *str);
int			check_no_opned_pr(t_node *data);
int			find_it(char *s, char c);
int			check_qoats(char *val);
int			others_checker(t_node *data);
int			check_redirction(t_node *data);
int			valid_next(TokenType type);
int			check_append(t_node *data);
int			ft_isascii(int c);
char		*ft_strndup(char *s, size_t n);
int			operator(char c);
int			syntax_checker(t_node *data);
char		**ft_split_word(char *str, char *word);
void		add_to_list(t_node **head, t_node *new);
t_node		*add_new_node(TokenType type, char *val);
int			ft_isalnum(char c);
char		*extract_word(char *s);
void    	add_to_cmd(t_cmd **head, t_cmd *new);
t_cmd   	*new_cmd(t_node *node);
char		*expander(t_node *node, t_env *head);
t_cmd		*data_maker(t_node *head, t_env *env);
t_expand	*new_expand(State state, char *val);
void		add_expand(t_expand **head, t_expand *new);
char		*expand_and_join(t_expand *head);
char		*expand_this(char *str);
char		*herdoc(t_env *env, char *exit);

#endif