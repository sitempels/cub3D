#include "../inc/cub3D.h"

bool	valid_file_extension(char *filename, char *ext)
{
	if (ft_strnstrend(filename, ext, ft_strlen(filename)) != NULL)
		return true;
	ft_printf_fd(STDERR_FILENO, "Error: incorrect or missing file extension. Expected: %s\n", ext);
	return false;
}

int	main(int ac, char **av)
{
	//t_game *game;
	
	int	fd;

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
	return 0;

}
