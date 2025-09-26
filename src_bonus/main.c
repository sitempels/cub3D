/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaland <agaland@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:36:01 by agaland           #+#    #+#             */
/*   Updated: 2025/09/26 17:10:46 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	game_init(t_game *game);
static int	mlx_initialisation(t_game *game);
static int	texture_init(t_game *game);

int	main(int ac, char **av)
{
	int		fd;
	t_game	game;

	if (ac != 2)
		return (ft_error(USAGE, NULL), 1);
	fd = open(av[1], O_DIRECTORY);
	if (fd != -1)
		return (ft_error(ERR_DIR, NULL), 1);
	close(fd);
	if (!valid_file_extension(av[1], ".cub", '\0'))
		return (1);
	ft_memset(&game, 0, sizeof(t_game));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_error(ERR_OPEN, NULL), 1);
	if (parse_file(fd, &game) == 1)
		return (close(fd), cleanup_game(&game), 1);
	close(fd);
	if (mlx_initialisation(&game))
		return (clean_all(&game), 1);
	game_init(&game);
	if (cub3d(&game) != 0)
		return (cleanup_game(&game), 1);
	cleanup_game(&game);
	return (0);
}

static void	game_init(t_game *game)
{
	game->minimap = 0;
	if (game->screen_width < game->screen_height)
		game->mini_size = game->screen_width * 0.33 / game->max_x;
	else
		game->mini_size = game->screen_height * 0.33 / game->max_y;
	game->mini_width = game->mini_size * game->max_x;
	game->mini_height = game->mini_size * game->max_y;
	game->show_fps = 0;
	game->show_fov = 1;
	game->show_col = 0;
	game->frametime = 1;
	return ;
}

static int	mlx_initialisation(t_game *game)
{
	t_data	*data;

	data = (t_data *) malloc(sizeof(t_data));
	memset(data, 0, sizeof(t_data));
	game->data = data;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	if (texture_init(game))
		return (1);
	data->win = mlx_new_window(data->mlx, game->screen_width,
			game->screen_height, "cub3D_bonus");
	if (!data->win)
		return (1);
	data->img = mlx_new_image(data->mlx, game->screen_width,
			game->screen_height);
	if (!data->img)
		return (1);
	data->addr = mlx_get_data_addr(data->img, &data->bpp,
			&data->l_length, &data->endian);
	if (!data->addr)
		return (1);
	return (0);
}

static int	texture_init(t_game *game)
{
	int			i;
	t_texture	*texture;

	i = 0;
	while (i < 4)
	{
		game->texture[i] = malloc(sizeof(t_texture));
		if (!game->texture[i])
			return (1);
		texture = game->texture[i];
		texture->wall = mlx_xpm_file_to_image(game->data->mlx,
				game->config->textures_path[i], &texture->width,
				&texture->height);
		if (!texture->wall)
		{
			texture->wall = NULL;
			return (ft_error(ERR_TEXT, game->config->textures_path[i]), 1);
		}
		texture->addr_w = mlx_get_data_addr(texture->wall, &texture->bpp,
				&texture->l_length, &texture->endian);
		if (!game->texture[i]->addr_w)
			return (ft_printf_fd(STDERR_FILENO, "Error\n"), 1);
		i++;
	}
	return (0);
}
