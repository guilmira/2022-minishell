/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:01:41 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/06 17:52:14 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void
	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*a;
	char	*b;

	if (dst && src)
	{
		a = (char *)src;
		b = (char *)dst;
		while (n > 0)
		{
			*b = *a;
			b++;
			a++;
			n--;
		}
	}
	return (dst);
}

int
	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1)
	{
		if (*str1 != *str2)
			break ;
		str1++;
		str2++;
	}
	return (*(const unsigned char *)str1 - *(const unsigned char *)str2);
}

void
	ft_str_swap(void *p1, void *p2)
{
	char	buffer[sizeof(char *)];

	ft_memcpy(buffer, p1, sizeof(char *));
	ft_memcpy(p1, p2, sizeof(char *));
	ft_memcpy(p2, buffer, sizeof(char *));
}

void
	ft_str_sort(void *v, int left, int right)
{
	void	*vt;
	void	*v3;
	int		i;
	int		last;
	int		mid;
	void	*vl;
	void	*vr;

	mid = (left + right) / 2;
	if (left >= right)
		return ;
	vl = (char *)(v + (left * sizeof(char *)));
	vr = (char *)(v + (mid * sizeof(char *)));
	ft_str_swap(vl, vr);
	last = left;
	i = left + 1;
	while (i <= right)
	{
		vt = (char *)(v + (i * sizeof(char *)));
		if (ft_strcmp(vl, vt) > 0)
		{
			++ last;
			v3 = (char *)(v + (last * sizeof(char *)));
			ft_str_swap(vt, v3);
		}
		i++;
	}
	v3 = (char *)(v + (last * sizeof(char *)));
	ft_str_swap(vl, v3);
	ft_str_sort(v, left, last - 1);
	ft_str_sort(v, last + 1, right);
}
