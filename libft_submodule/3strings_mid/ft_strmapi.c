/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:16:29 by guilmira          #+#    #+#             */
/*   Updated: 2021/05/31 10:21:11 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*ptr;

	i = -1;
	if (!s || !f)
		return (NULL);
	ptr = (char *) ft_calloc((ft_strlen(s) + 1), sizeof(*ptr));
	if (!ptr)
		return (NULL);
	while (s[++i])
		ptr[i] = (f)(i, s[i]);
	ptr[i] = '\0';
	return (ptr);
}
