int	**map_alloc(int	fd, size_t len, int *nbr_line)
{
	int	**map;
	char *line;

	line = gnl;
	if (!line)
	{
		map = (int **) malloc(sizeof(int *) * len);
		return (map);
	}
	n_lengh = ft_strlen(line);
	if (n_lengh > len)
		len = n_lengh
	map = map_alloc(fd, len, (*nbr_line) + 1);
	if (!map)
		blabla;
	map[nbr_line] = (int *) malloc(sizeof(int) * (*nbr_Line));
}

function appel
{
	map = map_alloc(fd, 0, 0);
}
