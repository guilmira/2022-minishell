/* int	exists_symbol_in_string(char *str, char sym)
{	
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] == sym)
			return (1);
	}
	return (0);
} */

/** PURPOSE : Obtains position in table that has the inmmeiate next collon
 * Example [echo "hello what i"s" up], will return the position 3. */
/* int	obtain_position_next_quote(char **table, int position, char *symbol)
{
	int	i;

	i = position;
	while (table[i])
	{
		if (exists_symbol_in_string(table[i], symbol[0]))
			return (i);
		i++;
	}
	return (i);
} */

/* char *string_without_quote(char *str, char *sym)
{
	char	*firsthalf;
	char	*secondhalf;
	char	*ptr;

	if (!str)
		return (NULL);
	ptr = NULL;
	firsthalf = NULL;
	secondhalf = NULL;
	if (str[0] == sym[0])
		return(ft_strdup(&str[1]));
	ptr = ft_strchr(str, sym[0]);
	if (!(ptr + 1))
		return (ft_strtrim(str, sym));
	firsthalf = ft_substr(str, 0, ptr - str);
	secondhalf = ft_strdup(ptr + 1);
	ptr = ft_strjoin(firsthalf, secondhalf);
	free(firsthalf);
	free(secondhalf);
	return (ptr);
} */


/** PURPOSE : Creates new string takin into account quotes. 
 *					--ALLOCATES MEMORY-- */
/* char *get_new_string(char **table, int initial, int final)
{
	char *new_str;
	char *tmp;
	int i;
	char *str_non_quote;

	if (!table)
		return (NULL);
	if (initial >= final)
		return (table[initial]);
	tmp = NULL;
	i = initial;
	str_non_quote = NULL;
	new_str = string_without_quote(table[i], "\"");
	if (!new_str)
		return (NULL);
		
	i++;
	while (table[i] && i <= final)
	{
		tmp = new_str;
		if (i == final)
		{
			char *str2 = first_quote_remove(table[i], "\"");
		}
		new_str = ft_strjoin(tmp, table[i]);
		if (!new_str)
		{
			free(tmp);
			return (NULL);
		}
		free(tmp);
		i++;
	}
	return (new_str);
} */

/** PURPOSE : Copies table insertinf newString if necessary. 
 *					--ALLOCATES MEMORY-- */
/* void replicate_table(char **new_table, char **table, int initial, int final, char *new_str)
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
			new_table[j] = ft_strdup(table[i]);
		j++;
	}
} */

/** PURPOSE : Main executer of fnct to rearrange quotes.
   * 					--ALLOCATES MEMORY-- */
/* char **remake_table(char **table, int initial, int final)
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
	{
		free(new_str);
		return (NULL);
	}
	replicate_table(new_table, table, initial, final, new_str);
	return (new_table);
} */

/** PURPOSE : Takes a table of strings and remakes it. */
/* char	**adjust_quote(char **table, char symbol)
{
	int		i;
	int		position;
	char	**new_table;
	char	**tmp_table;

	i = -1;
	tmp_table = NULL;
	new_table = table;
	while (table[++i])
	{
		if (non_closed_quote(table[i], symbol))
		{
			position = obtain_position_next_quote(table, i + 1, "\"");
			new_table = remake_table(table, i, position);
			if (!new_table)
				return (NULL);
			tmp_table = table;
			table = new_table;
			ft_free_split(tmp_table);
		}
	}
	return (new_table);
} */


/** PURPOSE : Takes a table of strings and erases the quotes.
 * It works for both " and '. Some examples: 
 * ls "-l-a"			--> 	ltable[0] = ls, table[1] = -l-a. */
/* char **remove_quote(char **table, char *symbol)
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
} */

/** PURPOSE : Takes a line with quotes, arranges it and clears it.
 * It works for both " and '. Some examples: 
 * ls "-l-a"			--> 	ltable[0] = ls, table[1] = -l-a 
 * ls "dir whatever"	--> 	table[0] = ls, table[1] = dir whatever */
/* char **quote_management(char **table)
{	
	char	**adjusted_line;
	char	**clean_line;

	//TODO prioratize function. either '  found first, or " found first.
	//then apply that to ' or ""
	adjusted_line = adjust_quote(table, '"');
	if (!adjusted_line)
		return (NULL);
	printlt(adjusted_line);
	clean_line = remove_quote(adjusted_line, "\"");
	if (!clean_line)
		return (NULL);
	return (clean_line);
} */