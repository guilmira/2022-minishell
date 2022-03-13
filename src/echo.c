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
void
	manage_output_redirection(t_arguments *args);

void
	print_output(char *const *args, int i, char *token, t_arguments *arg)
{
	t_command	*command_struct;

	command_struct = NULL;
	command_struct = ft_lst_position(arg->commands_lst, arg->command_number);
	if (!command_struct->command)
		return ;
	command_file_setup(command_struct, arg);
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
		print_output(args, i, token, arg);
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
