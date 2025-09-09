#include "../inc/cub3D.h"
#include "../gnl/get_next_line_bonus.h"


int	parse_file(int fd, t_game *game)
{
	int	rows;
	int	max_len;

	rows = 0;
	max_len = 0;
	if (process_map_recursive(fd, &game->map, &rows, &max_len) == 1)
		return (1);
	
	print_map(game->map, rows, max_len);
	return (0);
}

int	check_line(char *line, int *player_count)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW \n", line[i]))
		{
			ft_printf_fd(STDERR_FILENO, "Error: Invalid character <%c> inserted\n", line[i]);
			return(1);
		}
		if (ft_strchr("NSEW", line[i]))
		{
			(*player_count)++;
			if (*player_count > 1)
			{
				ft_printf_fd(STDERR_FILENO, "Error: Multiple players found\n");
				return (1);
			}
		}
		i++;		
	}
	return (0);
}

int	process_map_recursive(int fd, int ***matrix, int *rows, int *max_len)
{
	char 		*line;
	int			line_lenght;
	int			curr_row;
	static int	player_count;

	if ((get_next_line(fd, &line)) < 0)
		return (printf("Gnl Error\n"), 1);
	else if (!line)
		return (allocate_matrix(matrix, *rows));
	line_lenght = ft_strlen(line);
	if (line_lenght > *max_len)
		*max_len = line_lenght;
	curr_row = *rows;
	if (check_line(line, &player_count) == 1)
		return (1);
	(*rows)++;
	process_map_recursive(fd, matrix, rows, max_len);
	if (!*matrix)
		return (1);
	(*matrix)[curr_row] = malloc(sizeof(int) * (*max_len));
	if (!(*matrix)[curr_row])
		return (1);
	if (init_matrix(matrix, line, *max_len, curr_row, line_lenght) != 0)
	{
		free(line);
		return (1);
	}
	free(line);
	return (0);
}
