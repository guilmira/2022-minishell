/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:01:41 by asydykna          #+#    #+#             */
/*   Updated: 2021/12/08 11:56:12 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** SYNOPSIS: function for comparing two strings.
*/
int
	ft_strcmp(char *str1, char *str2)
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
	ft_str_swap(char **p1, char **p2)
{
	char	*temp;

	temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

/*
** SYNOPSIS: function for sorting string arrays using quicksort method.
*/
void
	ft_str_sort(char *arr[], unsigned int len)
{
	unsigned int	i;
	unsigned int	pivot;

	if (len <= 1)
		return ;
	pivot = 0;
	i = 0;
	while (i < len)
	{
		if (ft_strcmp(arr[i], arr[len - 1]) < 0)
			ft_str_swap(arr + i, arr + pivot++);
		i++;
	}
	ft_str_swap(arr + pivot, arr + len - 1);
	ft_str_sort(arr, pivot++);
	ft_str_sort(arr + pivot, len - pivot);
}
