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
	write_child_status(const t_arguments *args, int *i)
{
	close(args->wpipe[0]);
	write(args->wpipe[1], i, sizeof(int));
	close(args->wpipe[1]);
}

void
	read_child_status(t_arguments *args)
{
	close(args->wpipe[1]);
	read(args->wpipe[0], &args->status, sizeof(int));
	close(args->wpipe[0]);
}