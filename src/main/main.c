/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:48:34 by yaajagro          #+#    #+#             */
/*   Updated: 2025/01/31 18:05:55 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_env_list(t_env *env_list);

char	**convert_env_to_array(t_env *env_list)
{
	int		count;
	t_env	*temp;
	int		i;
	char	*temp_value;
	char	**env_array;

	count = count_env_list(env_list);
	env_array = malloc((count + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	temp = env_list;
	i = 0;
	while (i < count)
	{
		env_array[i] = ft_strjoin(temp->key, "=");
		temp_value = ft_strjoin(env_array[i], temp->value);
		free(env_array[i]);
		env_array[i] = temp_value;
		temp = temp->next;
		i++;
	}
	env_array[count] = NULL;
	return (env_array);
}

void init_shell(t_shell *shell, char **envp)
{
    t_env *env_list;
    env_list = ft_env_create(envp);
    shell->env = convert_env_to_array(env_list);
}

int main(int ac, char **av, char **env)
{
    t_data data;
    (void)ac;
    (void)av;

    data.env = env;
    // data.env_var = ft_env_create(env);
    clear_terminal();
    signal(SIGINT, ft_sighandler);
    signal(SIGINT, ft_sighandler);
    signal(SIGQUIT, ft_sighandler);
    while (1)
        prompt(env);
    return (0);
}
