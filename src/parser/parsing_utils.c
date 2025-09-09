#include "../inc/cub3D.h"

int	allocate_matrix(int ***matrix, int rows)
{
	*matrix = malloc(sizeof(int *) * (rows));
	if (!*matrix)
		return (1);
	return (0);
}

int	init_matrix(int ***matrix, char *line, int max_len, int curr_row, int line_lenght)
{
	int	j;

	j = 0;
	while (j < max_len)
	{
		(*matrix)[curr_row][j] = -1;
		j++;
	}
	j = 0;
	while (j < line_lenght)
	{
		if (line[j] == ' ' || line[j] == '\n')
			(*matrix)[curr_row][j] = EMPTY;
		else if (line[j] == '0')
			(*matrix)[curr_row][j] = FLOOR;
		else if (line[j] == '1')
			(*matrix)[curr_row][j] = WALL;
		else if (line[j] == 'N')
			(*matrix)[curr_row][j] = N;
		else if (line[j] == 'S')
			(*matrix)[curr_row][j] = S;
		else if (line[j] == 'E')
			(*matrix)[curr_row][j] = E;
		else if (line[j] == 'W')
			(*matrix)[curr_row][j] = W;
		else
			return (1);
		j++;
	}
	return (0);
}

char	*ft_strnstrend(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	if (needle[0] == 0)
		return ((char *) haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		ptr = (char *) &haystack[i];
		while (haystack[i + j] == needle[j] && haystack[i + j] && i + j < len)
			j++;
		if (needle[j] == '\0' && haystack[i + j] == '\0')
			return (ptr);
		i++;
	}
	return (NULL);
}
