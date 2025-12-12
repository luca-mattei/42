// srcs/parsing/parse_utils.c
#include "cube3d.h"

char	*trim_whitespace(char *str)
{
	char	*end;
	static char trimmed[1024];
	int		len;

	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == 0)
	{
		trimmed[0] = '\0';
		return (trimmed);
	}

	ft_strcpy(trimmed, str);
	len = ft_strlen(trimmed);
	end = trimmed + len - 1;
	while (end > trimmed && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r'))
		end--;

	// Null terminate
	end[1] = '\0';

	return (trimmed);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}