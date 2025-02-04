/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_help.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:19:27 by iezzam            #+#    #+#             */
/*   Updated: 2025/02/04 13:28:22 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/execution.h"

// static int ft_is_valid_identifier(char *str)
// {
//     int i;

//     if (!str || !str[0])
//         return (-1);

//     if ('0' <= str[0] && str[0] <= '9')
//         return (-1);
//     i = 0;
//     while (str[i])
//     {
//         if (!(('0' <= str[i] && str[i] <= '9') || 
//               ('a' <= str[i] && str[i] <= 'z') || 
//               ('A' <= str[i] && str[i] <= 'Z') || 
//               str[i] == '_'))
//             return (-1);
//         i++;
//     }

//     return 0;
// }

// static char *ft_get_slice(char *str, int *right, char stop)
// {
//     char *slice;
//     int left = *right;
//     int i = 0;

//     if (!str)
//         return (NULL);

//     while (str[*right] && str[*right] != stop)
//         (*right)++;

//     slice = (char *)malloc(sizeof(char) * (*right - left + 1)); // +1 for '\0'
//     if (!slice)
//         return (NULL);

//     while (left < *right)
//         slice[i++] = str[left++];
    
//     slice[i] = '\0';
//     return (slice);
// }

// static char *ft_remove_plus_from_slice1(char *old_slice1)
// {
//     char *new_slice1 = ft_substr(old_slice1, 0, ft_strlen(old_slice1) - 1);
//     free(old_slice1);
//     return (new_slice1);
// }

// static void ft_export_init(t_export *expt, char *str)
// {
//     expt->right = 0;
//     expt->slice1 = ft_get_slice(str, &expt->right, '=');
//     expt->equal = (str[expt->right] == '=');
//     expt->right += expt->equal; // Move past '=' if exists
//     expt->append = ft_is_valid_identifier(expt->slice1);
//     expt->slice2 = ft_get_slice(str, &expt->right, '\0');
//     expt->value = NULL;
// }

// void ft_export_help(char *str, t_env **env, int *exit_status)
// {
//     t_export expt;

//     ft_export_init(&expt, str);

//     if (expt.append == -1)
//         return (*exit_status = 1, ft_export_error(expt.slice1, expt.slice2, expt.equal, expt.append));

//     if (expt.append)
//         expt.slice1 = ft_remove_plus_from_slice1(expt.slice1);

//     if (expt.append && !expt.equal)
//         return (*exit_status = 1, ft_export_error(expt.slice1, expt.slice2, expt.equal, expt.append));

//     if (expt.slice1 && !ft_strncmp(expt.slice1, "_", 1))
//         return (free(expt.slice1), free(expt.slice2));

//     expt.value = ft_env_search(*env, expt.slice1);

//     if (!expt.equal && expt.value)
//         return (free(expt.value), free(expt.slice1), free(expt.slice2));

//     free(expt.value);

//     if (ft_env_update(env, expt.slice1, expt.slice2, expt.append))
//     {
//         if (expt.slice2 && expt.equal)
//             ft_env_add(env, expt.slice1, expt.slice2, 1);
//         else
//             ft_env_add(env, expt.slice1, expt.slice2, 0);
//     }
// }


static int	ft_is_valid_identifier(char *str)
{
	int	i;

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
				('0' <= str[i] && str[i] <= '9')
				|| ('a' <= str[i] && str[i] <= 'z')
				|| ('A' <= str[i] && str[i] <= 'Z')
				|| str[i] == '_'
			)
		)
			return (-1);
		i++;
	}
	return (0);
}

static char	*ft_get_slice(char *str, int *right, char stop)
{
	char	*slice;
	int		left;
	int		i;

	if (!str)
		return (NULL);
	left = *right;
	while (str[*right] && str[*right] != stop)
		(*right)++;
	slice = (char *)malloc(sizeof(char) * (*right - left) + 1);
	i = 0;
	while (left < *right)
		slice[i++] = str[left++];
	slice[i] = '\0';
	return (slice);
}

static char	*ft_remove_plus_from_slice1(char *old_slice1)
{
	char	*new_slice1;

	new_slice1 = ft_substr(old_slice1, 0, ft_strlen(old_slice1) - 1);
	free(old_slice1);
	return (new_slice1);
}

static void	ft_export_init(t_export *expt, char *str)
{
	expt->right = 0;
	expt->slice1 = ft_get_slice(str, &expt->right, '=');
	expt->equal = 1 * (str[expt->right] == '=');
	expt->right += 1 * (str[expt->right] == '=');
	expt->append = ft_is_valid_identifier(expt->slice1);
	expt->slice2 = ft_get_slice(str, &expt->right, '\0');
	expt->value = NULL;
}

void	ft_export_help(char *str, t_env **env, int *exit_status)
{
	t_export	expt;

	ft_export_init(&expt, str);
	if (expt.append == -1)
		return (*exit_status = 1, \
		ft_export_error(expt.slice1, expt.slice2, expt.equal, expt.append));
	if (expt.append)
		expt.slice1 = ft_remove_plus_from_slice1(expt.slice1);
	if (expt.append && !expt.equal)
		return (*exit_status = 1, \
		ft_export_error(expt.slice1, expt.slice2, expt.equal, expt.append));
	if (expt.slice1 && !ft_strncmp(expt.slice1, "_", 1))
		return (free(expt.slice1), free(expt.slice2));
	expt.value = ft_env_search(*env, expt.slice1);
	if (!expt.equal && expt.value)
		return (free(expt.value), free(expt.slice1), free(expt.slice2));
	free(expt.value);
	if (ft_env_update(env, expt.slice1, expt.slice2, expt.append))
	{
		if (expt.slice2 && expt.equal)
			ft_env_add(env, expt.slice1, expt.slice2, 1);
		else
			ft_env_add(env, expt.slice1, expt.slice2, 0);
	}
}
