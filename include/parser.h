/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:48:43 by yaajagro          #+#    #+#             */
/*   Updated: 2025/03/20 01:23:49 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "stdbool.h"
#    define BUFFER_SIZE 5000000

typedef struct s_node
{
	TokenType		type;
	char			*value;
	bool			visit;
	int				hr_fd;
	struct s_node	*next;
}	t_node;

typedef enum e_state
{
	NORMAL,
	IN_SQUOTE,
	IN_DQUOTE
}	t_state;

typedef struct s_expand
{
	t_state			state;
	char			*val;
	struct s_expand	*next;
}	t_expand;

typedef struct s_buffer
{
	char			*val;
	struct s_buffer	*next;
}	t_buffer;

t_node		*lexer_init(const char *str);
int			check_no_opned_pr(t_node *data);
int			find_it(char *s, char c);
int			check_qoats(char *val);
int			others_checker(t_node *data);
int			valid_next(TokenType type);
int			check_append(t_node *data);
int			operator(char c);
int			syntax_checker(t_node *data);
void		add_to_list(t_node **head, t_node *new);
t_node		*add_new_node(TokenType type, char *val);
int			is_inside_quotes(char *str, char *cur);
char		*extract_word(char *s);
void		add_to_cmd(t_cmd **head, t_cmd *new);
t_cmd		*new_cmd(t_node *node);
char		*expander(char *str, t_env *head);
t_cmd		*data_maker(t_node *head, t_env *env);
t_expand	*new_expand(t_state state, char *val);
void		add_expand(t_expand **head, t_expand *new);
char		*expand_and_join(t_expand *head, t_env *env);
char		*expand_this(char *str, t_env *env);
int			is_sperator(char c);
char		*get_before(char *s);
char		*get_after(char *s);
char		*extract_name(char *str);
void		set_space_zero(char *tmp);
void		set_zero_space(char **s);
void		set_space_zero_qoats(char *tmp);
t_cmd		*get_last_cmd(t_cmd *head);
void		set_empty_str(char **s);
char		**join_args_adv(char **s1, char **s2);
int			herdoc(t_env *env, t_cmd *commnd, t_cmd **head, char *exit);
void		handle_single_quote(char **input, t_expand **head, t_state *state);
void		handle_double_quote(char **input, t_expand **head, t_state *state);
void		handle_normal_text(char **input, t_expand **head, t_state state);

#endif