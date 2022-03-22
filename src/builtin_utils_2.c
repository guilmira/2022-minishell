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
	//does it lost here?
	if (!var)
		return (false);
	if (!ft_strchr(needle, '='))
	{
		free(var);
		return (true);
	}
	free(var);
	return (false);
}

/*
** SYNOPSIS: allows get rid of quotes in the beginning and
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

bool
	has_equal_sign(char *const *envp, int i)
{
	bool	has_equal_sign;

	has_equal_sign = false;
	if (ft_strchr(envp[i], '='))
		has_equal_sign = true;
	return (has_equal_sign);
}

char *
	get_env_var_body(char **envp, bool do_expand, int i, int len)
{
	char	*var;

	if (do_expand)
		var = ft_strdup(envp[i]);
	else
	{
		if (has_equal_sign(envp, i))
			var = ft_strdup(envp[i] + len + 1);
		else
			var = ft_strdup(envp[i] + len);
	}
	return (var);
}
