/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:36:01 by agaland           #+#    #+#             */
/*   Updated: 2025/09/23 16:22:19 by agaland          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	int		fd;
	t_game	game;

	if (ac != 2)
		return (ft_error(USAGE, NULL), 1);
	if (!valid_file_extension(av[1], ".cub", '\0'))
		return (1);
	ft_memset(&game, 0, sizeof(t_game));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_error(ERR_OPEN, NULL), 1);
	if (parse_file(fd, &game) == 1)
		return (close(fd), cleanup_game(&game), 1);
	close(fd);
	print_map(game.map, game.max_y, game.max_x); // SUPPRIMER PRINT
	/*---INIITALIZER TO MOVE-------*/
	game.minimap = 1;
	game.show_fps = 0;
	/*-----------------------------*/
	if (display_handler(&game) != 0)
		return (cleanup_game(&game), 1);
	cleanup_game(&game);
	return (0);
}
