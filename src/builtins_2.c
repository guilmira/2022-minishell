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
	msh_export(char **args __attribute__((unused)), char *envp[] __attribute__((unused)))
{
	return (1);
}

int
	msh_unset(char **args __attribute__((unused)), char *envp[] __attribute__((unused)))
{
	return (1);
}

int
	msh_env(char **args __attribute__((unused)), char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	printf("\n");
	return (1);
}

int
	msh_exit(char **args __attribute__((unused)), char *envp[] __attribute__((unused)))
{
	return (0);
}
