/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0files.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:48:01 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/09 15:13:49 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Searchs on arguments for '<' symbol. */
static int	file_symbol_detected(char *str, char symbol)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == symbol && (str[i + 1] == ' ' || !str[i + 1]))
		{
			if (i == 0)
				return (1);
			else if (i != 0)
			{
				str[i - 1] = ' ';
				return (1);
			}
		}
	}
	return (0);
}

/** PURPOSE : Is a file being introduced as an input to the program? */
static int	file_detector(int argc, char *argv[], char symbol)
{
	int	i;

	i = -1;
	while (++i < argc)
		if (file_symbol_detected(argv[i], symbol))
		{
			if (file_exists(argv[i - 1]))
				return (1);
			else
				return (2);
		}
	return (0);
}

//ver tema counters

/** PURPOSE : Load into struct file descriptors for input. */
static int	file_arrangement(char *argv[], int argc, t_arguments *args)
{
	int	i;

	i = -1;
	while (++i < argc)
		if (file_symbol_detected(argv[i], '<'))
			args->file_input = argv[i - 1];
	return (0);
}

/** PURPOSE : Load into struct file descriptors for output. */
static int	file_arrangement_out(int argc, char *argv[], t_arguments *args)
{
	int	i;
	

	i = -1;
	while (++i < argc)
		if (file_symbol_detected(argv[i], '>'))
			args->file_output = argv[i + 1];
	return (0);
}

/** PURPOSE : Load arguments into structure. 
 * 1. Checks whether files are given as parameter.
 * 2. Sets adresses to input and output files.
 * 3. Sets some of the values of "args" struct. */
int	file_management(int argc, char *argv[], t_arguments *args)
{
	int	modifier;
	int	flag;

	modifier = 0;
	args->total_commands = argc;
	flag = 0;
	flag = file_detector(argc, argv, '<');
	if (flag)
	{
		if (flag == 2)
			ft_shutdown("file does not exist\n", 0, args);
		args->flag_file_in = 1;
		file_arrangement(argv, argc, args);
		args->total_commands = argc - 2;
		modifier = 2;
	}
	flag = file_detector(argc, argv, '>');
	printf("here %i\n", flag);
	if (flag)
	{
		args->flag_file_out = 1;
		file_arrangement_out(argc, argv, args);
		args->total_commands = argc - 2;
	}
	args->command_number = 0;
	return (modifier);
}
