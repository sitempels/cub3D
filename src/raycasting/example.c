int	**alloc_map(int nbr_line)
{
	int	byte;
	int	**map;

	byte = read();
	if (byte < 0)
		return (NULL);
	if (byte == 0)
	{
		map = (int **) malloc(sizeof(int *) * nbr_line);
		return (map);
	}
	if (verif_ligne)
		return (NULL);	
	map = alloc_map(nbr_line + 1);
	if (!map)
		return (NULL);
	map[nbr_line] = (int *) malloc(sizeof(int) * line_length);
	if (map[nbr_line])
	{
		clean_tabo
		return (NULL);
	}
	traitement buffer
}
