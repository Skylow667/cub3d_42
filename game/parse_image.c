/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 19:22:15 by averdon           #+#    #+#             */
/*   Updated: 2023/01/25 13:19:35 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parse_image(t_game *game)
{
	char	*name_sprite[4];
	int	i;

	name_sprite[0] = game->data->text_no;
	name_sprite[1] = game->data->text_ea;
	name_sprite[2] = game->data->text_so;
	name_sprite[3] = game->data->text_we;
	ft_fdprintf(1, "%s\n%s\n%s\n%s\n", game->data->text_no, game->data->text_ea, game->data->text_so, game->data->text_we);
	/*name_sprite[0] = "textures/north_text.xpm";
	name_sprite[1] = "textures/south_text.xpm";
	name_sprite[2] = "textures/west_text.xpm";
	name_sprite[3] = "textures/east_text.xpm";*/
	t_img		*img;
	int			width;
	int			length;
	int			y;
	int			x;
	int			r;
	int			g;
	int			b;
	unsigned int color;
	unsigned int **image;
	i = 0;
	while (i < 4)
	{
		img = ft_calloc(1, sizeof(t_img));
		img->img = mlx_xpm_file_to_image(game->mlx, name_sprite[i], &width, &length);
		img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
		image = ft_calloc(256, sizeof(unsigned int *));
		y = 0;
		while (y < length)
		{
			x = 0;
			image[y] = ft_calloc(256, sizeof(unsigned int));
			while (x < width)
			{

				r = img->addr[y * img->line_length + x * (img->bits_per_pixel / 8) + 2];
				g = img->addr[y * img->line_length + x * (img->bits_per_pixel / 8) + 1];
				b = img->addr[y * img->line_length + x * (img->bits_per_pixel / 8)];
				color = (r << 16) + (g << 8) + b;
				image[y][x] = color;
				x++;
			}
			y++;
		}
		game->images[i] = image;
		i++;
	}
	
}
