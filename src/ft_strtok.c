/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:11:35 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/20 18:11:36 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *
	search_str_for_token(const char *str, const char *delim)
{
	const char	*delim_copy;

	while (*str != '\0')
	{
		delim_copy = delim;
		while (*delim_copy != '\0')
			if (*delim_copy++ == *str)
				return ((char *) str);
		++str;
	}
	return (NULL);
}

size_t
	get_prefix_len(const char *str, const char *delim)
{
	const char	*p;
	const char	*delim_copy;
	size_t		len;

	len = 0;
	p = str;
	while (*p != '\0')
	{
		delim_copy = delim;
		while (*delim_copy != '\0')
		{
			if (*p == *delim_copy)
				break ;
			if (*delim_copy == '\0')
				return (len);
			else
				++len;
			++delim_copy;
		}
		++p;
	}
	return (len);
}

char
	*ft_strtok(char *str, const char *delim)
{
	static char	*old_str;
	char		*token;

	if (str == NULL)
		str = old_str;
	/* Scan leading delimiters.  */
	str += get_prefix_len(str, delim);
	if (*str == '\0')
	{
		old_str = str;
		return (NULL);
	}
	/* Find the end of the token.  */
	token = str;
	str = search_str_for_token(token, delim);
	if (str == NULL)
		/* This token finishes the string.  */
		old_str = ft_memchr(token, '\0', INT_MAX);
	else
	{
		/* Terminate the token and make OLDS point past it.  */
		*str = '\0';
		old_str = str + 1;
	}
	return (token);
}
