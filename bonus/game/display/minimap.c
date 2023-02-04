/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:36:40 by nlocusso          #+#    #+#             */
/*   Updated: 2023/02/04 15:43:01 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	put_player_map(t_game *game, int x, int y)
{
	my_mlx_pixel_put(game->screen_img, y, x, 0xFF0101);
	my_mlx_pixel_put(game->screen_img, y - 1, x, 0xFF0101);
	my_mlx_pixel_put(game->screen_img, y + 1, x, 0xFF0101);
	my_mlx_pixel_put(game->screen_img, y, x - 1, 0xFF0101);
	my_mlx_pixel_put(game->screen_img, y, x + 1, 0xFF0101);
	my_mlx_pixel_put(game->screen_img, y - 1, x - 1, 0xFF0101);
	my_mlx_pixel_put(game->screen_img, y + 1, x + 1, 0xFF0101);
	my_mlx_pixel_put(game->screen_img, y - 1, x + 1, 0xFF0101);
	my_mlx_pixel_put(game->screen_img, y + 1, x - 1, 0xFF0101);
}

void	put_one_block(t_game *game, unsigned int color)
{
	int				x;
	int				y;

	x = game->x_minimap;
	while (x < game->x_minimap + 16)
	{
		y = game->y_minimap;
		while (y < game->y_minimap + 16)
		{
			my_mlx_pixel_put(game->screen_img, y, x, color);
			y++;
		}
		x++;
	}
}

void	put_assets(t_game *game, unsigned int **color)
{
	int				x;
	int				y;

	x = game->x_minimap;
	while (x < game->x_minimap + 16)
	{
		y = game->y_minimap;
		while (y < game->y_minimap + 16)
		{
			my_mlx_pixel_put(game->screen_img, y, x, color[x - game->x_minimap][y - game->y_minimap]);
		//	printf("\nX player: %d X pixel: %d\n", (int)game->player->x, x);
		//	printf("Y player: %d Y pixel: %d\n", (int)game->player->y, y);
			if (x == (int)game->player->x && y == (int)game->player->y)
			{
				printf("ok\n");
				put_player_map(game, x, y);
			}
			y++;
		}
		x++;
	}
}

int	calculate_arrow(int	a, int b, int mode)
{
	if (mode == 1)
		return ((a - b) / 2);
	else
		return ((b - a + 16) / 2);
}

void	put_arrow(t_game *game, int	i_minimap, int	j_minimap, int mode)
{
	int	x;
	int	y;

	x = i_minimap;
	while (x < i_minimap + 16)
	{
		y = j_minimap + calculate_arrow(x, i_minimap, mode);
		while (y < j_minimap + 16 - calculate_arrow(x, i_minimap, mode))
		{
			if (game->y_minimap == j_minimap)
				my_mlx_pixel_put(game->screen_img, y, x, 0x00ffd8);
			else
				my_mlx_pixel_put(game->screen_img, x, y, 0x00ffd8);
			y++;
		}
		x++;
	}
}

void	put_cursor(t_game *game, int x, int y)
{
	static int	x_minimap;
	static int	y_minimap;

	if (!game)
	{
		x_minimap = x;
		y_minimap = y;
		return ;
	}
	if (game->player->orientation >= 45 && game->player->orientation <= 135)
	{
		game->x_minimap = x_minimap;
		game->y_minimap = y_minimap + 16;
		put_arrow(game, game->y_minimap, game->x_minimap, 1);
	}
	else if (game->player->orientation >= 135
		&& game->player->orientation <= 225)
	{
		game->x_minimap = x_minimap - 16;
		game->y_minimap = y_minimap;
		put_arrow(game, game->x_minimap, game->y_minimap, 0);
	}
	else if (game->player->orientation >= 225
		&& game->player->orientation <= 315)
	{
		game->x_minimap = x_minimap;
		game->y_minimap = y_minimap - 16;
		put_arrow(game, game->y_minimap, game->x_minimap, 0);
	}
	else
	{
		game->x_minimap = x_minimap + 16;
		game->y_minimap = y_minimap;
		put_arrow(game, game->x_minimap, game->y_minimap, 1);
	}
}

void	put_pixel_color(t_game *game, int x, int y)
{
	if (game->map[x][y] == '1' || game->map[x][y] == '\0')
		put_assets(game, game->minimap_img[1]);
	else if (ft_strchr("NSEW0", game->map[x][y]))
		put_assets(game, game->minimap_img[0]);
	else if (ft_strchr("D", game->map[x][y]))
		put_assets(game, game->minimap_img[2]);
	else if (ft_strchr("doO", game->map[x][y]))
		put_assets(game, game->minimap_img[3]);
	else
		put_one_block(game, 0);
}

void	trace_circle(t_game *game)
{
	int	x;
	int	y;
	int	d;

	x = 5 * 16;
	y = 108;
	d = 1 - x;
	while (x > y)
	{
		my_mlx_pixel_put(game->screen_img, x, y, 0xF30606);
		y++;
		if (d < 0)
			d = d + 2 * y + 1;
		else
		{
			x--;
			d = d + (2 * x) - (2 * y) + 1;
		}
	}
}

void	open_minimap(t_game *game)
{
	int			x;
	int			y;
	int			value_x;
	int			value_y;

	game->x_minimap = 20;
	x = (int)(game->player->x / SIZE_BLOCK) - 5;
	if (x < 0)
	{
		value_x = 6 - x;
		x = 0;
	}
	else
		value_x = 6;
	while (x < (int)(game->player->x / SIZE_BLOCK + value_x))
	{
		game->y_minimap = 20;
		y = (int)(game->player->y / SIZE_BLOCK) - 5;
		if (y < 0)
		{
			value_y = 6 - y;
			y = 0;
		}
		else
			value_y = 6;
		while (y < (int)(game->player->y / SIZE_BLOCK + value_y))
		{
			put_pixel_color(game, x, y);
			if (x == (int)(game->player->x / SIZE_BLOCK)
				&& y == (int)(game->player->y / SIZE_BLOCK))
				put_cursor(NULL, game->x_minimap, game->y_minimap);
			y++;
			game->y_minimap += 16;
		}
		x++;
		game->x_minimap += 16;
	}
	put_cursor(game, 0, 0);
	//trace_circle(game);
}
