/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_so_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:23:49 by averdon           #+#    #+#             */
/*   Updated: 2023/02/12 15:19:11 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main_so_long(int argc, char **argv, t_game *game)
{
	t_double_list	*map;

	map = parsing(argc, argv);
	game->vars = ft_calloc(1, sizeof(t_vars));
	game->vars->mlx = game->mlx;
	game->vars->window = game->window;
	initialize_var(game->vars, map, argc, argv);
	put_black_screen(game->vars);
	randomize_enemies(game->vars);
	display_map(game->vars);
	display_background(game->vars);
	mlx_put_image_to_window(game->vars->mlx, game->vars->window,
		game->vars->player->sprite[game->vars->player->frame],
		game->vars->player->x % (SIZE_BLOCK_SL * 10) + X_LEFT_UP_CORNER_GAME, game->vars->player->y % (SIZE_BLOCK_SL * 10) + Y_LEFT_UP_CORNER_GAME);
	mlx_put_image_to_window(game->vars->mlx, game->vars->window,
		game->vars->array_ptr_sprite[14], SIZE_BLOCK_SL * 10 + 10 + X_LEFT_UP_CORNER_GAME, SIZE_BLOCK_SL + Y_LEFT_UP_CORNER_GAME);
	/*
	mlx_hook(vars->window, KeyPress, KeyPressMask, key_hook, vars);
	mlx_hook(vars->window, DestroyNotify, StructureNotifyMask,
		close_window, vars);
	mlx_loop_hook(vars->mlx, animation_and_movement, vars);
	mlx_loop(vars->mlx);
	*/
	return (0);
}
