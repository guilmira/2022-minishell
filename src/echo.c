/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:56:48 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/10 20:35:19 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	print_output(char *const *args, int i, char *token)
{
	ft_putstr_fd(token, 1);
	if (args[i + 1])
		ft_putstr_fd(" ", 1);
	free_pointers(1, token);
}

/*
** SYNOPSIS: checks arguments passed to echo command and prints them.
*/
void
	loop_and_print_echo_args(char **args, t_arguments *arg, int i)
{
	char	*token;

	token = NULL;
	while (args[i])
	{
		token = ft_strdup(args[i]);
		print_output(args, i, token);
		i++;
	}
	set_status(arg, 0);
}

void
	check_n_option(char *const *args, int *i, bool *have_option)
{
	if (!ft_memcmp(args[(*i)], "-n", 3))
	{
		(*have_option) = true;
		(*i) += 1;
	}
}

/*
** SYNOPSIS: builtin echo command.
*/
int
	msh_echo(char **args, t_arguments *arg)
{
	int		i;
	bool	have_option;

	printf("when it enters echo %s\n", args[1]);
	i = 1;
	have_option = false;
	if (args[i])
	{
		check_n_option(args, &i, &have_option);
		loop_and_print_echo_args(args, arg, i);
	}
	if (!have_option)
		ft_putstr_fd("\n", 1);
	set_status(arg, 0);
	return (1);
}
