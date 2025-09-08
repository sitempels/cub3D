#include "../inc/cub3D.h"

int	main(int ac, char **av)
{
	//t_game *game;
	
	if (ac != 2)
	{
		ft_printf_fd(STDERR_FILENO, "Wrong number of arguments\nUsage : ./cub3d <filename.cub>");
		return (1);
	}
	
	return 0;

}