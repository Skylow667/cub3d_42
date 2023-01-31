/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 20:21:26 by averdon           #+#    #+#             */
/*   Updated: 2023/01/31 13:17:53 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "display/display.h"
#include "game.h"

void	interact(t_game *game)
{
	t_raycast	raycast;
	long		time;

	raycast.pos_x = game->player->x / SIZE_BLOCK;
	raycast.pos_y = game->player->y / SIZE_BLOCK;
	raycast.dir_x = cos(radian_value(game->player->orientation));
	raycast.dir_y = sin(radian_value(game->player->orientation));
	raycast.plane_x = cos(radian_value(game->player->orientation + 90));
	raycast.plane_y = sin(radian_value(game->player->orientation + 90));
	calculate_delta_and_dist(WIDTH_SCREEN / 2, &raycast);
	detect_wall(game, &raycast);
	calculate_dist_perp_wall(&raycast);
	if (raycast.dist_perp_wall > (double)1)
		return ;
	if (game->map[raycast.map_x][raycast.map_y] == 'D')
	{
		time = calculate_time();
		while (calculate_time() - time < 2000)
		{
			display_screen(game, 1);
			printf("%ld interact\n", calculate_time() - game->time_start);
		}
		game->map[raycast.map_x][raycast.map_y] = 'd';
	}
	else if (game->map[raycast.map_x][raycast.map_y] == 'd')
	{
		game->map[raycast.map_x][raycast.map_y] = 'D';
	}
	/*
	else if (game->map[raycast.map_x][raycast.map_y] == '1')
		add_graffiti(game);
	*/
}
