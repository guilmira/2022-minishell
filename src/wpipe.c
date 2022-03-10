/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wpipe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:39:49 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/09 10:39:50 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	write_pipe_to(int *pipe, int *to)
{
	close(pipe[0]);
	write(pipe[1], to, sizeof(int));
	close(pipe[1]);
}

void
	read_pipe_from(int *pipe, int *from)
{
	close(pipe[1]);
	read(pipe[0], from, sizeof(int));
	close(pipe[0]);
}
