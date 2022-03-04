/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:25:18 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/02 11:25:19 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool
	var_have_val(char **envp, char *needle)
{
	char	*var;

	var = get_env_var(envp, needle, false);
	if (!var)
		return (false);
	if (!ft_strchr(needle, '='))
		return (true);
	return (false);
}

/*
** SYNOPSIS: allows to get rid of quotes in the beginning and
** at the end of environmental variable.
*/
void
	get_rid_of_quotes(char **args, size_t i, char *str)
{
	char	*tmp;
	size_t	len;
	size_t	j;

	if (ft_strchr(str, '=') && (*(ft_strchr(str, '=') + 1) == '\''
								|| *(ft_strchr(str, '=') + 1) == '\"'))
	{
		len = ft_strlen(str);
		tmp = (char *)malloc(len - 1 * sizeof(char));
		j = -1;
		while (str[++j] != '=')
			tmp[j] = str[j];
		tmp[j] = str[j];
		j++;
		while (j + 1 < len - 1)
		{
			tmp[j] = str[(j + 1)];
			j++;
		}
		tmp[len - 2] = '\0';
		free(args[i]);
		args[i] = tmp;
	}
}
