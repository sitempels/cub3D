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

char 	**parse_map(int fd, int *rows, int *max_len)
{
	char 	*line;
	char 	**matrix;
	int		line_lenght;
	int		curr_row;

	line = get_next_line(fd);
	if (!line)
	{
		matrix = malloc(sizeof(char *) * (*rows + 1));
		return (matrix);
	}
	line_lenght = ft_strlen(line);
	if (line_lenght > *max_len)
		*max_len = line_lenght;
	//printf("max_len: %d\n", *max_len);
	curr_row = *rows;
	(*rows)++;
	parse_map(fd, rows, max_len);
	if (!matrix)
		return NULL;
	matrix[curr_row] = malloc(sizeof(char) * (*max_len));
	if (!matrix[curr_row])
		return (NULL);
	matrix[curr_row] = line;
	//printf("curr_row: %d\n", curr_row);
	//printf("LAST ROW: %d\n", *rows);
	return (matrix);
}

int	main(int ac, char **av)
{
	int	fd;
	int	i;
	int	rows;
	int	len;
	char **matrix;

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
	len = 0;
	rows = 0;
	matrix = parse_map(fd, &rows, &len);
	i = 0;
	while (matrix[i])
	{
		printf("%s", matrix[i]);
		i++;
	}
	return 0;

}
