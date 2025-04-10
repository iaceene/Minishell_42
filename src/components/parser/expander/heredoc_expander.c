/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:28:39 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/10 11:42:37 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

char	*expand_this_str(char *str, t_env *env, int exit)
{
	char	*word;

	word = extract_name(str);
	(void)env;
	(void)exit;
	printf("[%s]\n", word);
	return (word);
}

char	*heredoc_expander(char *str, t_env	*env, int exit)
{
	if (!str || !env)
		return (NULL);
	if (!find_it(str, '$'))
		return (str);
	return (expand_this_str(str, env, exit));
}