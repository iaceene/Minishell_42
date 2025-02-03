/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 01:36:19 by yaajagro          #+#    #+#             */
/*   Updated: 2025/02/03 01:39:21 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

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

typedef struct {
    TokenType type;   // Type of token
    char *value;      // Value of the token (e.g., command name, argument)
} Token;

typedef struct {
    const char *input;  // Input string
    int position;       // Current position in the input
    int length;         // Length of the input
} Lexer;


Lexer   *init_lexer(const char *input);
Token   *get_next_token(Lexer *lexer);

#endif