#include "../includes/minishell.h"

// returns pointer to the first character ('$') of the formatted variable in the string and sets 'size' to the number of characters of this variable
char	*find_var(char *str, size_t *size)
{
	if (!str || !size)
		return (NULL);
	*size = 0;
	while (*str && *str != '$')
		str++;
	if (*str == '$')
		*size = strdlen(str, " \t\n|<>");
	return (str);
}
