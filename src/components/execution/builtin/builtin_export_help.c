/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_help.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:19:27 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/04 15:44:13 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

static int ft_is_valid_identifier(char *str)
{
	int i;

	if (!str || !str[0])
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && !str[i + 1] && i != 0)
			return (1);
		if ('0' <= str[i] && str[i] <= '9' && i == 0)
			return (-1);
		if (
			!(
				('0' <= str[i] && str[i] <= '9') || ('a' <= str[i] && str[i] <= 'z') || ('A' <= str[i] && str[i] <= 'Z') || str[i] == '_'))
			return (-1);
		i++;
	}
	return (0);
}

static char *ft_get_slice(char *str, int *pos, char stop)
{
	char *slice;
	int left;
	int i;

	if (!str)
		return (NULL);
	left = *pos;
	while (str[*pos] && str[*pos] != stop)
		(*pos)++;
	slice = (char *)malloc(sizeof(char) * (*pos - left) + 1);
	i = 0;
	while (left < *pos)
		slice[i++] = str[left++];
	slice[i] = '\0';
	return (slice);
}

static char *ft_remove_plus_from_key_part(char *old_key_part)
{
	char *new_key_part;

	new_key_part = ft_substr(old_key_part, 0, ft_strlen(old_key_part) - 1);
	free(old_key_part);
	return (new_key_part);
}

static void ft_export_init(t_export *expt, char *str)
{
	expt->pos = 0;
	expt->key_part = ft_get_slice(str, &expt->pos, '=');
	expt->has_equal = 1 * (str[expt->pos] == '=');
	expt->pos += 1 * (str[expt->pos] == '=');
	expt->is_append = ft_is_valid_identifier(expt->key_part);
	expt->value_part = ft_get_slice(str, &expt->pos, '\0');
	expt->existing_value = NULL;
}

void ft_export_help(char *str, t_env **env, int *exit_status)
{
	t_export expt;

	ft_export_init(&expt, str);
	if (expt.is_append == -1)
		return (*exit_status = 1,
				print_export_error(expt.key_part, expt.value_part, expt.has_equal, expt.is_append));
	if (expt.is_append)
		expt.key_part = ft_remove_plus_from_key_part(expt.key_part);
	if (expt.is_append && !expt.has_equal)
		return (*exit_status = 1,
				print_export_error(expt.key_part, expt.value_part, expt.has_equal, expt.is_append));
	if (expt.key_part && !ft_strncmp(expt.key_part, "_", 1))
		return (free(expt.key_part), free(expt.value_part));
	expt.existing_value = ft_env_search(*env, expt.key_part);
	if (!expt.has_equal && expt.existing_value)
		return (free(expt.existing_value), free(expt.key_part), free(expt.value_part));
	free(expt.existing_value);
	if (ft_env_update(env, expt.key_part, expt.value_part, expt.is_append))
	{
		if (expt.value_part && expt.has_equal)
			ft_env_add(env, expt.key_part, expt.value_part, 1);
		else
			ft_env_add(env, expt.key_part, expt.value_part, 0);
	}
}
