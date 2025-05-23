/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 12:00:00 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 12:00:00 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_sprites(t_data *data)
{
	if (data->img)
	{
		if (data->img->player)
			mlx_destroy_image(data->mlx, data->img->player);
		if (data->img->wall)
			mlx_destroy_image(data->mlx, data->img->wall);
		if (data->img->floor)
			mlx_destroy_image(data->mlx, data->img->floor);
		if (data->img->box)
			mlx_destroy_image(data->mlx, data->img->box);
		if (data->img->target)
			mlx_destroy_image(data->mlx, data->img->target);
		if (data->img->box_on_target)
			mlx_destroy_image(data->mlx, data->img->box_on_target);
		if (data->img->exit)
			mlx_destroy_image(data->mlx, data->img->exit);
		if (data->img->player_on_target)
			mlx_destroy_image(data->mlx, data->img->player_on_target);
	}
}

void	free_array(char **array1, char **array2)
{
	int	i;

	i = 0;
	if (array1 != NULL)
	{
		while (array1[i] != NULL)
			free(array1[i++]);
		free(array1);
	}
		i = 0;
	if (array2 != NULL)
	{
		while (array2[i] != NULL)
			free(array2[i++]);
		free(array2);
	}
}

int	data_destroyer(t_data *data)
{	if (data->map || data->game_map)
		free_array(data->game_map, data->map);
	if (data->m_map)
		free(data->m_map);
	if (data->fd >= 0)
		close(data->fd);
	free_sprites(data);
	if (data->img)
	{
		if (data->mlx)
		{
			mlx_loop_end(data->mlx);
			mlx_destroy_window(data->mlx, data->mlx_window);
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
		free(data->img);
	}
	if (data)
		free(data);
	exit(0);
}
