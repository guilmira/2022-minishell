/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:56:48 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/13 13:56:42 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		printf("%s", token);
		if (args[i + 1])
			printf(" ");
		free_pointers(1, token);
		i++;
	}
	set_status(arg, 0);
}

void
	check_n_option(char *const *args, int *i, bool *have_option)
{
	int		j;
	char	c;
	char	d;

	c = 'n';
	if (!ft_memcmp(args[(*i)], "-n", 2))
	{
		j = 2;
		while (args[(*i)][j])
		{
			d = args[(*i)][j];
			if (ft_memcmp(&d, &c, 1))
				break ;
			j++;
		}
		if (!args[(*i)][j])
		{
			(*have_option) = true;
			(*i) += 1;
		}
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

	i = 1;
	have_option = false;
	if (args[i])
	{
		check_n_option(args, &i, &have_option);
		loop_and_print_echo_args(args, arg, i);
	}
	if (!have_option)
		printf("\n");
	set_status(arg, 0);
	return (1);
}
