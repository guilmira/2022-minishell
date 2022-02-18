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

char
	*ft_multistr_concat(int count, ...)
{
	int		i;
	size_t	len;
	va_list	ap;
	char	*s;
	char	*ret;
	char	*dst;
	char	*src;

	len = 0;
	if (count < 1)
		return (NULL);
	va_start(ap, count);
	i = -1;
	while (++i < count)
	{
		s = va_arg(ap, char *);
		len += strlen(s);
	}
	va_end(ap);
	ret = (char *)malloc(len + 1);
	if (!ret)
		return (NULL);
	dst = ret;
	va_start(ap, count);
	i = -1;
	while (++i < count)
	{
		src = va_arg(ap, char *);
		while (*src)
		{
			*dst++ = *src++;
		}
	}
	va_end(ap);
	ret[len] = '\0';
	return (ret);
}
