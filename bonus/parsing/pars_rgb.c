/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:06:04 by nlocusso          #+#    #+#             */
/*   Updated: 2023/01/26 13:07:01 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_rgb_value(t_data *data)
{
	int	i;

	i = 0;
	while (i != 3)
	{
		if (ft_strlen(data->text_f[i]) > 7 || ft_strlen(data->text_c[i]) > 7
			|| ft_atoi(data->text_f[i]) < 0 || ft_atoi(data->text_f[i]) > 255
			|| ft_atoi(data->text_c[i]) < 0 || ft_atoi(data->text_c[i]) > 255)
		{
			free_data(data);
			print_error("Error\nRGB colors can only be between 0 and 256\n");
		}
		i++;
	}
}

void	pars_rgb_color(t_data *data)
{
	char	*tmp;

	if (ft_len_tab(data->text_f) != 3 || ft_len_tab(data->text_c) != 3)
	{
		free_data(data);
		print_error("Error\nBad RGB color\n");
	}
	tmp = ft_strtrim(data->text_f[0], " \t");
	free(data->text_f[0]);
	data->text_f[0] = tmp;
	tmp = ft_strtrim(data->text_c[0], " \t");
	free(data->text_c[0]);
	data->text_c[0] = tmp;
	check_rgb_value(data);
	data->hex_f = (ft_atoi(data->text_f[0]) << 16)
		+ (ft_atoi(data->text_f[1]) << 8) + ft_atoi(data->text_f[2]);
	data->hex_c = (ft_atoi(data->text_c[0]) << 16)
		+ (ft_atoi(data->text_c[1]) << 8) + ft_atoi(data->text_c[2]);
}
