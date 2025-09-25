/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stempels <stempels@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:55:57 by stempels          #+#    #+#             */
/*   Updated: 2025/09/25 13:47:36 by stempels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_wall_text(t_dda *dda, t_ray *ray);
static void	texture_mapping(t_game *game, t_dda *dda, t_ray *ray, int wall[4]);
static void	print_wall(t_game *game, int wall[4], int tex[2], double text_p[3]);

void	draw_wall(t_game *game, t_dda *dda, t_ray *ray)
{
	int	wall[4];

	wall[0] = (int)(game->screen_height / ray->dist);
	wall[1] = -wall[0] / 2 + game->screen_height / 2;
	if (wall[1] < 0)
		wall[1] = 0;
	if (game->minimap)
		if (ray->x < game->mini_width + MINI_BORDER_L)
			if (wall[1] < game->mini_height + MINI_BORDER_L)
				wall[1] = game->mini_height + MINI_BORDER_L;
	wall[2] = wall[0] / 2 + game->screen_height / 2;
	if (wall[2] >= game->screen_height)
		wall[2] = game->screen_height;
	texture_mapping(game, dda, ray, wall);
	return ;
}

static void	texture_mapping(t_game *game, t_dda *dda, t_ray *ray, int wall[4])
{
	int		tex[2];
	double	wall_x;
	double	tex_pos[3];

	wall[3] = get_wall_text(dda, ray);
	if (ray->side == 0)
		wall_x = game->player->pos[1] + ray->dist * dda->raydir[1];
	else
		wall_x = game->player->pos[0] + ray->dist * dda->raydir[0];
	wall_x -= (int)wall_x;
	if (game->texture[wall[3]])
	{
		tex[0] = (int)(wall_x * (double)(game->texture[wall[3]]->width));
		if (ray->side == 0 && dda->raydir[0] > 0)
			tex[0] = game->texture[wall[3]]->width - tex[0] - 1;
		if (ray->side == 1 && dda->raydir[1] < 0)
			tex[0] = game->texture[wall[3]]->width - tex[0] - 1;
		tex_pos[1] = 1.0 * game->texture[wall[3]]->height / wall[0];
		tex_pos[0] = (wall[1] - game->screen_height / 2 + wall[0] / 2);
		tex_pos[0] *= tex_pos[1];
	}
	tex_pos[2] = ray->x;
	print_wall(game, wall, tex, tex_pos);
	return ;
}

static void	print_wall(t_game *game, int wall[4], int tex[2], double tex_pos[3])
{
	int				y;
	int				p_pos;
	unsigned int	color;
	t_texture		texture;

	y = wall[1];
	while (y < wall[2])
	{
		tex[1] = (int)tex_pos[0];
		tex_pos[0] += tex_pos[1];
		texture = *game->texture[wall[3]];
		p_pos = (tex[1] * texture.l_length) + tex[0] * (texture.bpp / 8);
		color = *(unsigned int *)&texture.addr_w[p_pos];
		px_put(game->data, tex_pos[2], y, color);
		y++;
	}
	return ;
}

static int	get_wall_text(t_dda *dda, t_ray *ray)
{
	int	wall_text;

	if (ray->side == 0)
	{
		wall_text = EA;
		if (dda->raydir[ray->side] < 0)
			wall_text = WE;
	}
	if (ray->side == 1)
	{
		wall_text = SO;
		if (dda->raydir[ray->side] < 0)
			wall_text = NO;
	}
	return (wall_text);
}
