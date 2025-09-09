#include "../inc/cub3D.h"
#include "gnl/get_next_line_bonus.h"


bool	valid_file_extension(char *filename, char *ext)
{
	if (ft_strnstrend(filename, ext, ft_strlen(filename)) != NULL)
		return true;
	ft_printf_fd(STDERR_FILENO, "Error: incorrect or missing file extension. Expected: %s\n", ext);
	return false;
}

/* int	check_line(char *line, int *player_count)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW ", line[i]))
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
} */


int	parse_map(int fd, int ***matrix, int *rows, int *max_len)
{
	char 	*line;
	int		line_lenght;
	int		curr_row;
	int		j;

	line = get_next_line(fd);
	if (!line)
	{
		*matrix = malloc(sizeof(int *) * (*rows));
		return (0);
	}
	line_lenght = ft_strlen(line);
	if (line_lenght > *max_len)
		*max_len = line_lenght;
	curr_row = *rows;
	(*rows)++;
	parse_map(fd, matrix, rows, max_len);
	if (!*matrix)
		return (1);
	(*matrix)[curr_row] = malloc(sizeof(int) * (*max_len));
	if (!(*matrix)[curr_row])
		return (1);
	if (init_map(matrix, line, *max_len, curr_row, line_lenght) != 0)
	{
		free(line);
		return (1);
	}
	free(line);
	return (0);
}

int	main(int ac, char **av)
{
	int	fd;
	int	rows;
	int	max_len;
	int **matrix;

	matrix = NULL;
	if (ac != 2)
	{
		ft_printf_fd(STDERR_FILENO, "Wrong number of arguments\nUsage : ./cub3d <filename.cub>\n");
		return (1);
	}
	if (!valid_file_extension(av[1], ".cub"))
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("open"), 1);
	rows = 0;
	max_len = 0;
	if (parse_map(fd, &matrix, &rows, &max_len) == 1)
		return (1);
	print_map(matrix, rows, max_len);

	return 0;

}
