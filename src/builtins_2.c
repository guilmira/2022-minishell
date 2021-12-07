/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:55:52 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/03 17:56:01 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int
	msh_export(char **args __attribute__((unused)), char *envp[])
{
	int		n;
	int		i;
	char	**arr;

	n = 0;
	while (envp[n])
		n++;
	arr = malloc((n + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		arr[i] = envp[i];
		i++;
	}
	arr[i] = NULL;
	ft_str_sort(arr, n);
	print_str_arr(arr);
	printf("\n");
	free(arr);
	return (1);
}



int
	msh_unset(char **args __attribute__((unused)), char *envp[] __attribute__((unused)))
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		tmp = ft_strjoin(args[i], "=");
		len = ft_strlen(tmp);
		j = 0;
		while (envp[j])
		{
			if (!ft_strncmp(envp[j], tmp, len))
			{
				envp[j] = NULL;
				while (envp[j + 1])
				{
					envp[j] = envp[j + 1];
					envp[j + 1] = NULL;
					j++;
				}
				break ;
			}
			j++;
		}
		printf("%s\n", args[i]);
		i++;
	}
	return (1);
}

int
	msh_env(char **args __attribute__((unused)), char *envp[])
{
	print_str_arr(envp);
	printf("\n");
	return (1);
}

int
	msh_exit(char **args __attribute__((unused)), char *envp[] __attribute__((unused)))
{
	return (0);
}
