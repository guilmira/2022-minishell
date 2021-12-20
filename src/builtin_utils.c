/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:36:14 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/10 12:07:59 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char*
	ft_concat(const char *s1, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1 * sizeof(char));
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2 + 1);
	return (result);
}

void
	set_status(t_arguments *arg, int status)
{
	arg->status = status;
}

int
	get_fd(char *path) //what if arg->file_output is NULL, or the user wants to output to sterr??
{
	int	fd;

	if (path)
		fd = fileno(fopen(path, "w")); //fopen is not allowed
	else
		fd = 1;
	return (fd);
}

void
	free_pointers(int num, ...)
{
	va_list	ap;
	int		i;
	void	*p;

	i = 0;
	va_start(ap, num);
	while (i < num)
	{
		p = va_arg(ap, void *);
		if (p)
		{
			free(p);
			p = NULL;
		}
		i++;
	}
	va_end(ap);
}
