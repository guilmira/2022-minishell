/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 11:26:31 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/17 11:26:32 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** SYNOPSIS: deletes environmental variable.
*/
void
	delete_env_var(t_arguments *arg, size_t len, const char *tmp)
{
	int		i;
	char	*tmp2;

	i = 0;
	while (arg->envp[i])
	{
		if (!ft_strncmp(arg->envp[i], tmp, len))
		{
			tmp2 = arg->envp[i];
			arg->envp[i] = NULL;
			free_pointers(1, tmp2);
			while (arg->envp[i + 1])
			{
				arg->envp[i] = arg->envp[i + 1];
				arg->envp[i + 1] = NULL;
				i++;
			}
			return ;
		}
		i++;
	}
}

/*
** SYNOPSIS: builtin unset command.
*/
int
	msh_unset(char **args, t_arguments *arg)
{
	int		i;
	size_t	len;
	char	*tmp;

	if (get_arr_len(args) < 2)
	{
		perror("unset: not enough arguments"); //WTF? unset: not enough arguments: No such file or directory
		set_status(arg, 1);
	}
	else
	{
		i = 1;
		while (args[i])
		{
			tmp = ft_strjoin(args[i], "=");
			len = ft_strlen(tmp);
			delete_env_var(arg, len, tmp);
			free(tmp);
			i++;
		}
		set_status(arg, 0);
	}
	return (1);
}
