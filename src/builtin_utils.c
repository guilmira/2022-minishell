/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:36:14 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/10 12:07:59 by guilmira         ###   ########.fr       */
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

/*
** SYNOPSIS: sets status of executed command.
*/
void
	set_status(t_arguments *arg, int status)
{
	arg->status = status;
}

/*
** SYNOPSIS: frees pointers passed as arguments and sets them to NULL.
** First arguments should indicate the quantity of passed pointers.
*/
void
	free_pointers(int num, ...)
{
	va_list	ap;
	int		i;
	void	*p;

	i = 0;
	va_start(ap, num);
	while (i < num)
	{
		p = va_arg(ap, void *);
		if (p)
		{
			free(p);
			p = NULL;
		}
		i++;
	}
	va_end(ap);
}

char *
	get_env_val(t_arguments *arg, size_t len, const char *tmp)
{
	int		i;
	char	*env;
	char	**arr;

	i = 0;
	while (arg->envp[i])
	{
		if (!ft_strncmp(arg->envp[i], tmp, len))
		{
			env = arg->envp[i];
			arr = ft_split(env, '=');
			env = ft_strdup(arr[1]);
			ft_free_split(arr);
			return (env);
		}
		i++;
	}
	return (NULL);
}

void
	set_shlvl_num(t_arguments *arg)
{
	static bool	shlvl_set;
	char		*tmp;
	int			num;
	char		**arr;
	char		*num_tmp;

	if (!shlvl_set)
	{
		tmp = get_env_val(arg, 5, "SHLVL");
		if (tmp)
		{
			num = ft_atoi(tmp);
			arr = (char **)get_arr(3, sizeof(char *));
			arr[0] = "export";
			free(tmp);
			num_tmp = ft_itoa(num + 1);
			tmp = ft_strjoin("SHLVL=", num_tmp);
			free_pointers(1, num_tmp);
			arr[1] = tmp;
			arr[2] = NULL;
			export_new_variables(arr, arg);
			//free(tmp);
			free(arr);
			//ft_free_split(arr);
		}
		shlvl_set = true;
	}
}
