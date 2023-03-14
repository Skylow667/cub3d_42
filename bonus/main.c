/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:03:15 by nlocusso          #+#    #+#             */
/*   Updated: 2023/03/14 16:19:38 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	init_data(&data);
	if (argc != 2 || check_extension(argv[1], ".cub") == 1)
		print_error("Error\nUsage: ./cub3D <map.cub>\n");
	if (early_parsing(argc, argv, &data) != 1)
	{
		start_game(&data, env);
		return (0);
	}
	else
		return (1);
}
