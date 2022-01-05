/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_booleans.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:33:05 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/04 12:08:04 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/** PURPOSE : Evaluates whether char is a sufix. */
int	is_sufix(char z)
{
	return (z == '-');
}

/** PURPOSE : Evaluates whether char is a pipe. */
int	is_pipe(char z)
{
	return (z == '|');
}

/** PURPOSE : Evaluates whether char is a pipe. */
int	is_file_symb(char z)
{
	return (z == '<' || z == '>');
}
