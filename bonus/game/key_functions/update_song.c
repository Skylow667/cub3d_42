/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_song.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:51:33 by averdon           #+#    #+#             */
/*   Updated: 2023/02/20 10:55:00 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	suppress_atmosphere_add_cheese(t_game *game)
{
	t_double_list	*buffer;
	t_song			*song;

	buffer = game->lst_sound;
	while (buffer)
	{
		song = buffer->content;
		if (song->type == DANCING_CHEESE || song->type == SPRAY)
			return ;
		buffer = buffer->next;
	}
	launch_song(game, DANCING_CHEESE);
	buffer = game->lst_sound;
	while (buffer)
	{
		song = buffer->content;
		if (song->type == ATMOSPHERE)
		{
			kill(song->pid, SIGKILL);
			suppress_node_sound(game, buffer);
		}
		buffer = buffer->next;
	}
}

void	suppress_cheese_add_atmosphere(t_game *game)
{
	t_double_list	*buffer;
	t_song			*song;

	buffer = game->lst_sound;
	while (buffer)
	{
		song = buffer->content;
		if (song->type == ATMOSPHERE)
			break ;
		else if (song->type == DANCING_CHEESE)
		{
			kill(song->pid, SIGKILL);
			suppress_node_sound(game, buffer);
		}
		buffer = buffer->next;
	}
	if (!buffer)
		launch_song(game, ATMOSPHERE);
}

void	update_song(t_game *game)
{
	if (game->lst_graff)
		suppress_atmosphere_add_cheese(game);
	else
		suppress_cheese_add_atmosphere(game);
}
