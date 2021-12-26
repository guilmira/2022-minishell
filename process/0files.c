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
			if (file_exists(argv[i + 1]))
				return (1);
	return (0);
}


//ver tema counters

/** PURPOSE : Load into struct file descriptors for input. */
static int	file_arrangement(char *argv[], t_arguments *args)
{
	int	i;

	i = 0;
	if (ft_strncmp(argv[i], "1files/", 7) == 0)
		args->file_input = argv[i];
	return (0);
}

/** PURPOSE : Load into struct file descriptors for output. */
static int	file_arrangement_out(int argc, char *argv[], t_arguments *args)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (++i < argc)
	{
		if (ft_strncmp(argv[i], "1files/", 7) == 0)
		{
			if (args->flag_file_in)
			{
				if (!counter++)
					;
				else
				{
					args->file_output = argv[i];
					return (1);
				}
			}
			else
			{
				args->file_output = argv[i];
			}
			
		}
	}
	return (0);
}

/** PURPOSE : Load arguments into structure. 
 * 1. Checks whether files are given as parameter.
 * 2. Sets adresses to input and output files.
 * 3. Sets some of the values of "args" struct. */
int	file_management(int argc, char *argv[], t_arguments *args)
{
	int	modifier;

	modifier = 0;
	args->total_commands = argc;
	if (file_detector(argc, argv, '<'))
	{
		args->flag_file_in = 1;
		file_arrangement(argv, args);
		args->total_commands = argc - 2;
		modifier = 2;
	}
	if (file_detector(argc, argv, '>'))
	{
		args->flag_file_out = 1;
		file_arrangement_out(argc, argv, args);
		args->total_commands = argc - 2;
	}
	args->command_number = 0;
	return (modifier);
}
