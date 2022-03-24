/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:01:17 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/08 14:31:19 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

	if (!ft_isalpha(*args[i]))
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

char
	*lenvp_routine(char *const *args, t_arguments *arg, int i, char *temp)
{
	delete_env_var(arg->lenvp, get_envv_len(args[i]), temp);
	free_pointers(1, temp);
	temp = "lenvp";
	return (temp);
}

char
	*envp_routine(char *const *args, t_arguments *arg, int i, char *temp)
{
	delete_env_var(arg->envp, get_envv_len(args[i]), temp);
	free_pointers(1, temp);
	temp = "envp";
	return (temp);
}

void
	mnge_status(t_arguments *args, int i)
{
	if (i > 1)
		set_status(args, i);
	else
		set_status(args, 0);
}
