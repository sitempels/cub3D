/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:36:01 by agaland           #+#    #+#             */
/*   Updated: 2025/09/11 16:35:10 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	int		fd;
	t_game	game;

	if (ac != 2)
	{
		ft_printf_fd(STDERR_FILENO,
			"Wrong number of arguments\nUsage : ./cub3d <filename.cub>\n");
		return (1);
	}
	if (!valid_file_extension(av[1], ".cub", '\0'))
		return (1);
	ft_memset(&game, 0, sizeof(t_game));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("open"), 1);
	if (parse_file(fd, &game) == 1)
		return (close(fd), 1);
	close(fd);
	display_handler(&game);
	cleanup_game(&game);
	return (0);
}
