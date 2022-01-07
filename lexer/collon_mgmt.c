/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collon_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:27 by guilmira          #+#    #+#             */
/*   Updated: 2022/01/07 13:56:35 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	obtain_position_next_collon(char **table, int position)
{
	int	i;

	i = position;
	while (table[i])
	{
		if (non_closed_collons(table[i], '"'))
			return (i);
		i++;
	}
	return (i);
}
//ls "jejej papap f" f

//OJO AQUI, REVISA BIEN. PODRIA HABER UNA CASUISTICA QUE DEJE ALGU PTR SIN LIBERAR
char *get_new_string(char **table, int initial, int final)
{
	char *new_str;
	char *tmp;
	int i;

	if (!table)
		return (NULL);
	if (initial >= final)
		return (table[initial]);
	tmp = NULL;
	i = initial;
	new_str = ft_strdup(table[i]);
	if (!new_str)
		return (NULL);
	printf("%s\n", new_str);
	i++;
	while (table[i] && i <= final)
	{
		tmp = new_str;
		new_str = ft_strjoin(tmp, " "); //habria que proteger
		free(tmp);
		tmp = new_str;
		new_str = ft_strjoin(tmp, table[i]); //habria que proteger
		free(tmp);
		i++;
	}
	return (new_str);
}

/** PURPOSE : Copies table. */
void replicate_table(char **new_table, char **table, int initial, int final, char *new_str)
{
	int i;
	int j;

	j = 0;
	i = -1;
	while (table[++i])
	{
		if (i == initial)
		{
			new_table[j] = new_str;
			i = final;	
		}
		else
			new_table[j] = table[i];
		printf("%i: %s\n", j, new_table[j]);
		j++;
	}
}

/** PURPOSE : Main executer of fnct to rearrange collons. */
char **remake_table(char **table, int initial, int final)
{
	int table_tokens;
	int new_table_tokens;
	char **new_table;
	char *new_str;

	new_str = NULL;
	new_table = NULL;
	new_str = get_new_string(table, initial, final);
	if (!new_str)
		return (NULL);
	table_tokens = count_table(table);
	new_table_tokens = table_tokens - (final - initial);
	new_table = ft_calloc(new_table_tokens + 1, sizeof(char *));
	if (!new_table)
		return (NULL);
	replicate_table(new_table, table, initial, final, new_str);
	return (new_table);
}

/** PURPOSE : Takes a table of strings and remakes it. */
char	**adjust_collons(char **table, char symbol)
{
	int	i;
	int	position;
	char **new_table;

	i = -1;
	new_table = table;
	while (table[++i]) //aqui revisar bien, xk al hacer un remake con un if, no siempre entra y cambia la ccosa.
	{
		if (non_closed_collons(table[i], symbol))
		{
			position = obtain_position_next_collon(table, i + 1);
			new_table = remake_table(table, i, position);
			i = position;
		}
	}
	return (new_table);
}

/** PURPOSE : Takes a table of strings and erases the collons.
 * It works for both " and '. Some examples: 
 * ls "-l-a"			--> 	ltable[0] = ls, table[1] = -l-a. */
char **remove_collons(char **table, char *symbol)
{
	int i;
	char **new_table;
	char *tmp;

	i = -1;
	new_table = table;
	while (table[++i])
	{
		if (table[i][0] == symbol[0])
		{
				tmp = ft_strtrim(table[i], symbol);
			if (!tmp) //TODO proteger bien
				return (NULL);
			free(table[i]);
			table[i] = tmp;
		}
	}
	return (new_table);
}

/** PURPOSE : Takes a line with collons, arranges it and clears it.
 * It works for both " and '. Some examples: 
 * ls "-l-a"			--> 	ltable[0] = ls, table[1] = -l-a 
 * ls "dir whatever"	--> 	table[0] = ls, table[1] = dir whatever */
char **collon_management(char **table)
{	
	char	**adjusted_line;
	char	**clean_line;

	//TODO prioratize function. either '  found first, or " found first.
	//then apply that to ' or ""
	adjusted_line = adjust_collons(table, '"');
	clean_line = remove_collons(adjusted_line, "\"");
	return (clean_line);
}