/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 12:00:00 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 12:00:00 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_chars(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (!available_char(map[i][j]))
			{
				ft_printf("Error\n%c Caracter inválido en mapa\n", map[i][j]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	update_location(t_data *data, int x, int y)
{
	data->pos_x = x;
	data->pos_y = y;
	data->moves++;
}

void	check_exit(t_data *data, int x, int y)
{
	(void)x; /* Evitar warning de parámetro no utilizado */
	(void)y; /* Evitar warning de parámetro no utilizado */
	if (data->m_map->boxes_placed == data->m_map->boxes)
	{
		ft_printf("¡Victoria! Completaste el nivel en %d movimientos.\n", 
			data->moves + 1);
		data_destroyer(data);
	}
	return ;
}

int	is_box(char c)
{
	if (c == 'C' || c == 'B')
		return (1);
	return (0);
}

void	push_box(t_data *data, int x, int y, int dir_x, int dir_y)
{
	int	next_x;
	int	next_y;

	next_x = x + dir_x;
	next_y = y + dir_y;
	if (next_x < 0 || next_y < 0 || next_x >= data->height 
		|| next_y >= data->width || data->game_map[next_x][next_y] == '1' 
		|| is_box(data->game_map[next_x][next_y]))
		return ;
	if (data->game_map[next_x][next_y] == '0')
	{
		data->game_map[next_x][next_y] = 'C';
		if (data->game_map[x][y] == 'B')
		{
			data->game_map[x][y] = 'G';
			data->m_map->boxes_placed--;
		}
		else
			data->game_map[x][y] = 'P';
		if (data->on_target)
			data->game_map[data->pos_x][data->pos_y] = 'X';
		else
			data->game_map[data->pos_x][data->pos_y] = '0';
		update_location(data, x, y);
		data->all_placed = (data->m_map->boxes_placed == data->m_map->boxes);
	}
	else if (data->game_map[next_x][next_y] == 'X')
	{
		data->game_map[next_x][next_y] = 'B';
		if (data->game_map[x][y] == 'B')
		{
			data->game_map[x][y] = 'G';
		}
		else
		{
			data->game_map[x][y] = 'P';
			data->m_map->boxes_placed++;
		}
		if (data->on_target)
			data->game_map[data->pos_x][data->pos_y] = 'X';
		else
			data->game_map[data->pos_x][data->pos_y] = '0';
		update_location(data, x, y);
		data->all_placed = (data->m_map->boxes_placed == data->m_map->boxes);
	}
}
