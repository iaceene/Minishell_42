/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:48:43 by iezzam            #+#    #+#             */
/*   Updated: 2025/03/11 23:31:01 by yaajagro         ###   ########.fr       */
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

typedef struct s_buffer
{
	char	*val;
	struct s_buffer *next;
}t_buffer;

t_node		*lexer_init(const char *str);
int			check_no_opned_pr(t_node *data);
int			find_it(char *s, char c);
int			check_qoats(char *val);
int			others_checker(t_node *data);
int			check_redirction(t_node *data);
int			check_no_opned_pr(t_node *data);
int			valid_next(TokenType type);
int			check_append(t_node *data);
int			operator(char c);
int			syntax_checker(t_node *data);
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
int	is_sperator(char c);
char	*get_before(char *s);
char	*get_after(char *s);
char	*extract_name(char *str);
void	handle_single_quote(char **input, t_expand **head, State *state);
void	handle_double_quote(char **input, t_expand **head, State *state);
void	handle_normal_text(char **input, t_expand **head, State state);

#endif