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

int
	mnge_output_redirection(t_arguments *arg, t_command *command_struct)
{
	int	save_stdout;

	save_stdout = 0;
	if (command_struct->list_out)
	{
		generate_output(command_struct->list_out, \
		command_struct->flag_file, arg);
		if (!arg->file_output)
		{
			command_struct->flag_file = -1;
			printf("File or directory not found\n");
		}
		if (arg->flag_file_out)
			save_stdout = dup(1);
		if (command_struct->flag_file == 2)
			output_to_file_append(arg->file_output);
		else if (command_struct->flag_file == 1)
			output_to_file(arg->file_output);
	}
	return (save_stdout);
}

int
	get_stdout_copy(t_arguments *arg, t_command *command_struct)
{
	//t_command	*command_struct;
	int			save_stdout;

//	command_struct = NULL;
//	command_struct = ft_lst_position(arg->commands_lst, arg->command_number);
	//if (!command_struct->command)
	//	return (0);
	if (command_struct->list_in)
	{
		search_input(command_struct->list_in, arg);
		if (arg->file_input)
			input_from_file(arg->file_input);
	}
	save_stdout = mnge_output_redirection(arg, command_struct);
	return (save_stdout);
}

/*
** SYNOPSIS: builtin echo command.
*/
int
	msh_echo(char **args, t_arguments *arg)
{
	int		i;
	bool	have_option;
	//int		save_stdout;

	//save_stdout = get_stdout_copy(arg);
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
	/*if (save_stdout)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		dup2(save_stdout, 1);
		close(save_stdout);
	}*/
	return (1);
}
