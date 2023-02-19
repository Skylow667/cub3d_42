/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:50:25 by averdon           #+#    #+#             */
/*   Updated: 2023/02/19 16:51:25 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	check_anim(t_game *game)
{
	t_double_list	*buffer;
	t_double_list	*next;
	t_song			*song;
	t_anim			*anim;
	t_graff			*graff;
	long			time;

	time = calculate_time();
	buffer = game->lst_anim;
	while (buffer)
	{
		anim = buffer->content;
		next = buffer->next;
		if (ft_strchr("oO", game->map[anim->x][anim->y])
			&& time - anim->time_anim_start >= 2000)
		{
			if (game->map[anim->x][anim->y] == 'o')
				game->map[anim->x][anim->y] = 'D';
			else
				game->map[anim->x][anim->y] = 'd';
			suppress_node_anim(game, anim->x, anim->y);
		}
		buffer = next;
	}
	buffer = game->lst_graff;
	while (buffer)
	{
		graff = buffer->content;
		if (time - graff->last_frame_changed >= 100)
		{
			graff->frame += 1;
			if (graff->frame == 6)
				graff->frame = 0;
			graff->last_frame_changed = time;
		}
		buffer = buffer->next;
	}
	buffer = game->lst_sound;
	while (buffer)
	{
		song = buffer->content;
		next = buffer->next;
		if ((song->type == SPRAY && time - song->start_time > 2500)
			|| (song->type == DOOR && time - song->start_time > 3500)
			|| (song->type == ATMOSPHERE && time - song->start_time > 313000)
			|| (song->type == DANCING_CHEESE && time - song->start_time > 252000)
			|| (song->type == PLAY_GAMEBOY && (time - song->start_time > 252000 || game->started_gameboy == false))
			|| (song->type == START_GAMEBOY && time - song->start_time > 235000))
		{
			if (song->type == PLAY_GAMEBOY && game->started_gameboy == false)
				kill(song->pid, SIGKILL);
			suppress_node_sound(game, buffer);
		}
		buffer = next;
	}
	if (game->lst_graff)
	{
		buffer = game->lst_sound;
		while (buffer)
		{
			song = buffer->content;
			if (song->type == DANCING_CHEESE || song->type == SPRAY)
				break ;
			buffer = buffer->next;
		}
		if (!buffer)
		{
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
	}
	else
	{
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
}
