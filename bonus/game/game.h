/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 21:03:49 by averdon           #+#    #+#             */
/*   Updated: 2023/02/20 16:39:32 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H

# define GAME_H

/*start_game.c*/
void	start_game(t_data *data, char **env);

/*initialize_game.c*/
void	initialize_game(t_game	*game, t_data *data);

/*song.c*/
void	launch_song(t_game *game, int mode);
void	suppress_node_sound(t_game *game, t_double_list *buffer);

#endif
