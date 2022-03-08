/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:01:17 by asydykna          #+#    #+#             */
/*   Updated: 2022/02/18 11:01:18 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** SYNOPSIS: concatenates two strings and returns new \0 terminated string.
*/
char*
	ft_concat(const char *s1, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1 * sizeof(char));
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2 + 1);
	return (result);
}

char *
	find_tail(char **args, int i)
{
	char	*tail;

	if (ft_strchr(args[i], '='))
		tail = ft_strdup(ft_strchr(args[i], '='));
	else
		tail = NULL;
	return (tail);
}

char *
	find_head(char **args, t_arguments *arg, int i, const char *tail)
{
	char	*head;
	size_t	var_len;

	if (tail)
	{
		var_len = ft_strchr(args[i], '=') - (args[i] + 1);
		head = get_env_var(arg->envp, ft_substr(args[i] + 1, 0, var_len),
				false);
	}
	else
		head = get_env_var(arg->envp, args[i] + 1, false);
	return (head);
}

/*
** SYNOPSIS: calculates the length of a variable up to the "=" sign.
*/
size_t
	get_envv_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

bool
	is_valid_var(char *const *args, t_arguments *arg, int i)
{
	char	*temp;

	if (!isalpha(*args[i]))
	{
		set_status(arg, 1);
		temp = ft_multistr_concat(3, "minishell: export: '", args[i],
				"': not a valid identifier");
		perror(temp);
		free_pointers(1, temp);
		return (false);
	}
	return (true);
}
