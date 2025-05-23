/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 12:00:00 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 12:00:00 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	loading(t_data *data, t_sprites *img)
{
	int	w;
	int	h;

	img->wall = mlx_xpm_file_to_image(data->mlx, "textures/wall.xpm", &w, &h);
	if (!img->wall)
		(ft_printf("Error\nFallo al cargar textura de pared\n"), 
			data_destroyer(data));
	img->floor = mlx_xpm_file_to_image(data->mlx, "textures/floor.xpm", &w, &h);
	if (!img->floor)
		(ft_printf("Error\nFallo al cargar textura de suelo\n"), 
			data_destroyer(data));
	img->box = mlx_xpm_file_to_image(data->mlx, "textures/box.xpm", &w, &h);
	if (!img->box)
		(ft_printf("Error\nFallo al cargar textura de caja\n"), 
			data_destroyer(data));
	img->player = mlx_xpm_file_to_image(data->mlx, "textures/player.xpm", &w, &h);
	if (!img->player)
		(ft_printf("Error\nFallo al cargar textura del jugador\n"), 
			data_destroyer(data));
	img->target = mlx_xpm_file_to_image(data->mlx, "textures/target.xpm", &w, &h);
	if (!img->target)
		(ft_printf("Error\nFallo al cargar textura de objetivo\n"), 
			data_destroyer(data));
	img->box_on_target = mlx_xpm_file_to_image(data->mlx, 
			"textures/box_on_target.xpm", &w, &h);
	if (!img->box_on_target)
		(ft_printf("Error\nFallo al cargar textura de caja en objetivo\n"), 
			data_destroyer(data));
	img->exit = mlx_xpm_file_to_image(data->mlx, "textures/exit.xpm", &w, &h);
	if (!img->exit)
		(ft_printf("Error\nFallo al cargar textura de salida\n"), 
			data_destroyer(data));
	img->player_on_target = mlx_xpm_file_to_image(data->mlx, 
			"textures/player_on_target.xpm", &w, &h);
	if (!img->player_on_target)
		(ft_printf("Error\nFallo al cargar textura de jugador en objetivo\n"), 
			data_destroyer(data));
}

void	put_image(t_data *data, char flag, int j, int i)
{
	if (flag == '1')
		mlx_put_image_to_window(data->mlx, data->mlx_window, 
			data->img->wall, j * 64, i * 64);
	else if (flag == '0')
		mlx_put_image_to_window(data->mlx, data->mlx_window, 
			data->img->floor, j * 64, i * 64);
	else if (flag == 'C')
		mlx_put_image_to_window(data->mlx, data->mlx_window, 
			data->img->box, j * 64, i * 64);
	else if (flag == 'P')
		mlx_put_image_to_window(data->mlx, data->mlx_window, 
			data->img->player, j * 64, i * 64);
	else if (flag == 'E')
		mlx_put_image_to_window(data->mlx, data->mlx_window, 
			data->img->exit, j * 64, i * 64);
	else if (flag == 'X')
		mlx_put_image_to_window(data->mlx, data->mlx_window, 
			data->img->target, j * 64, i * 64);
	else if (flag == 'B')
		mlx_put_image_to_window(data->mlx, data->mlx_window, 
			data->img->box_on_target, j * 64, i * 64);
	else if (flag == 'G')
		mlx_put_image_to_window(data->mlx, data->mlx_window, 
			data->img->player_on_target, j * 64, i * 64);
}

void	drawing(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->game_map[i])
	{
		j = 0;
		while (data->game_map[i][j])
		{
			if (data->game_map[i][j] == '1')
				put_image(data, '1', j, i);
			else if (data->game_map[i][j] == '0')
				put_image(data, '0', j, i);
			else if (data->game_map[i][j] == 'C')
				put_image(data, 'C', j, i);
			else if (data->game_map[i][j] == 'P')
				put_image(data, 'P', j, i);
			else if (data->game_map[i][j] == 'E')
				put_image(data, 'E', j, i);
			else if (data->game_map[i][j] == 'X')
				put_image(data, 'X', j, i);
			else if (data->game_map[i][j] == 'B')
				put_image(data, 'B', j, i);
			else if (data->game_map[i][j] == 'G')
				put_image(data, 'G', j, i);
			j++;
		}
		i++;
	}
}
