/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   early_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 20:58:05 by averdon           #+#    #+#             */
/*   Updated: 2023/01/18 20:59:52 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**early_parsing(int argc, char **argv)
{
	char	**map;
	char	*str;
	int		fd;
	int		i;

	if (argc != 2)
		return (NULL);
	fd = open(argv[1], O_RDONLY);
	map = NULL;
	str = get_next_line(fd);
	while (str)
	{
		map = append_to_tab(map, str);
		free(str);
		if (!map)
			return (NULL);
		str = get_next_line(fd);
	}
	i = 0;
	while (map[i])
	{
		map[i][ft_strlen(map[i]) - 1] = '\0';
		i++;
	}
	return (map);
}
