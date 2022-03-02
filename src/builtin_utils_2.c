/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:25:18 by asydykna          #+#    #+#             */
/*   Updated: 2022/03/02 11:25:19 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool
	var_have_val(char **envp, char *needle)
{
	char	*var;

	var = get_env_var(envp, needle);
	if (!var)
		return (false);
	if (!ft_strchr(needle, '='))
		return (true);
	return (false);
}
