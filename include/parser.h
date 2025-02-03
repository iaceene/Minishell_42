/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:58:16 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/03 02:12:30 by yaajagro         ###   ########.fr       */
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

typedef struct s_tocken{
    TokenType           type;   // Type of token
    char                *value;
    struct  s_tocken    *next;    
} t_tocken;

char	**ft_split_word(char *str, char *word);


#endif