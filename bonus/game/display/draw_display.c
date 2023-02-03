/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:29:09 by averdon           #+#    #+#             */
/*   Updated: 2023/02/03 13:17:37 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	color_to_draw(t_game *game, t_raycast *raycast,
		int tex_x, int tex_y)
{
	int	color;

	color = 0;
	if (find_square_2(game, raycast))
	{
		color = game->images[5][tex_y][tex_x];
		if (color >= 0)
			return (color);
	}
	if (game->map[raycast->map_x][raycast->map_y] == '1')
	{
		if (raycast->side == 0)
		{
			if (raycast->step_x == 1)
				color = game->images[0][tex_y][tex_x];
			else
				color = game->images[1][tex_y][tex_x];
		}
		else if (raycast->side == 1)
		{
			if (raycast->step_y == 1)
				color = game->images[2][tex_y][tex_x];
			else
				color = game->images[3][tex_y][tex_x];
		}
	}
	else
		color = game->images[4][tex_y][tex_x];
	return (color);
}

void	draw_wall(t_game *game, t_raycast *raycast, int x, double wall_x)
{
	double			tex_pos;
	double			step;
	int				tex_x;
	int				tex_y;
	int				color;

	step = 1.0 * 256 / raycast->line_height;
	tex_x = (int)(wall_x * (double)(256));
	if ((raycast->side == 0 && raycast->ray_dir_x > 0)
		|| (raycast->side == 1 && raycast->ray_dir_y < 0))
		tex_x = 256 - tex_x - 1;
	tex_pos = raycast->draw_start - HEIGHT_SCREEN / 2;
	tex_pos += raycast->line_height / 2;
	tex_pos *= step;
	while (raycast->draw_start < raycast->draw_end)
	{
		tex_y = (int)tex_pos % (256 - 1);
		tex_pos += step;
		color = color_to_draw(game, raycast, tex_x, tex_y);
		if (color >= 0)
			my_mlx_pixel_put(game->screen_img, x, raycast->draw_start, color);
		raycast->draw_start++;
	}
}

void	draw_line(t_game *game, int x, t_raycast *raycast)
{
	double			wall_x;
	int				i;
	long			time;

	time = calculate_time();
	if (ft_strchr("O", game->map[raycast->map_x][raycast->map_y])
		&& find_square(game, raycast->map_x, raycast->map_y))
	{
		if (raycast->side == 0)
			wall_x = raycast->pos_y - (double)((time - find_square(game, raycast->map_x, raycast->map_y)->time_anim_start)) / 2000 + raycast->dist_perp_wall * raycast->ray_dir_y;
		else
			wall_x = raycast->pos_x - (double)((time - find_square(game, raycast->map_x, raycast->map_y)->time_anim_start)) / 2000 + raycast->dist_perp_wall * raycast->ray_dir_x;
	}
	else if (ft_strchr("o", game->map[raycast->map_x][raycast->map_y])
		&& find_square(game, raycast->map_x, raycast->map_y))
	{
		if (raycast->side == 0)
			wall_x = raycast->pos_y - (double)(1 - (time - find_square(game, raycast->map_x, raycast->map_y)->time_anim_start)) / 2000 + raycast->dist_perp_wall * raycast->ray_dir_y;
		else
			wall_x = raycast->pos_x - (double)(1 - (time - find_square(game, raycast->map_x, raycast->map_y)->time_anim_start)) / 2000 + raycast->dist_perp_wall * raycast->ray_dir_x;
	}
	else
	{
		if (raycast->side == 0)
			wall_x = raycast->pos_y + raycast->dist_perp_wall * raycast->ray_dir_y;
		else
			wall_x = raycast->pos_x + raycast->dist_perp_wall * raycast->ray_dir_x;
	}
	wall_x -= floor(wall_x);
	i = 0;
	while (i < raycast->draw_start)
	{
		my_mlx_pixel_put(game->screen_img, x, i, game->hex_c);
		i++;
	}
	draw_wall(game, raycast, x, wall_x);
	while (raycast->draw_end < HEIGHT_SCREEN)
	{
		my_mlx_pixel_put(game->screen_img, x, raycast->draw_end, game->hex_f);
		raycast->draw_end++;
	}
}
