/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multistr_concat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:53:29 by asydykna          #+#    #+#             */
/*   Updated: 2022/02/15 11:53:30 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	loop_args(int count, int i, va_list ap, char *dst)
{
	char	*src;

	while (++i < count)
	{
		src = va_arg(ap, char *);
		while (*src)
		{
			*dst++ = *src++;
		}
	}
}

size_t
	get_len(int count, int i, size_t len, va_list ap)
{
	char	*s;

	while (++i < count)
	{
		s = va_arg(ap, char *);
		len += strlen(s);
	}
	return (len);
}

char
	*ft_multistr_concat(int count, ...)
{
	int		i;
	size_t	len;
	va_list	ap;
	char	*ret;
	char	*dst;

	len = 0;
	if (count < 1)
		return (NULL);
	va_start(ap, count);
	i = -1;
	len = get_len(count, i, len, ap);
	va_end(ap);
	ret = (char *)malloc(len + 1);
	if (!ret)
		return (NULL);
	dst = ret;
	va_start(ap, count);
	i = -1;
	loop_args(count, i, ap, dst);
	va_end(ap);
	ret[len] = '\0';
	return (ret);
}
