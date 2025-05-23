/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 12:00:00 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 12:00:00 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	move(t_data *data, int x, int y)
{
	int	dir_x;
	int	dir_y;

	dir_x = x - data->pos_x;
	dir_y = y - data->pos_y;
	if (data->game_map[x][y] == '1')
		return ;
	else if (is_box(data->game_map[x][y]))
		push_box(data, x, y, dir_x, dir_y);
	else if (data->game_map[x][y] == 'E' && data->all_placed)
	{
		ft_printf("¡Victoria! Completaste el nivel en %d movimientos.\n", 
			data->moves + 1);
		data_destroyer(data);
	}
	else if (data->game_map[x][y] == 'E' && !data->all_placed)
		ft_printf("Necesitas colocar todas las cajas en objetivos.\n");
	else if (data->game_map[x][y] == '0' || data->game_map[x][y] == 'X')
	{
		if (data->game_map[x][y] == 'X')
			data->on_target = 1;
		else
			data->on_target = 0;
		data->game_map[x][y] = data->on_target ? 'G' : 'P';
		if (data->on_target)
			data->game_map[data->pos_x][data->pos_y] = 
				data->game_map[data->pos_x][data->pos_y] == 'G' ? 'X' : '0';
		else
			data->game_map[data->pos_x][data->pos_y] = 
				data->game_map[data->pos_x][data->pos_y] == 'G' ? 'X' : '0';
		update_location(data, x, y);
	}
	drawing(data);
	ft_printf("Movimientos: %d\n", data->moves);
}

int	keys_press(int key, t_data *data)
{
	if (key == UP_W || key == UP_ARROW)
		move(data, data->pos_x - 1, data->pos_y);
	else if (key == DOWN_S || key == DOWN_ARROW)
		move(data, data->pos_x + 1, data->pos_y);
	else if (key == LEFT_A || key == LEFT_ARROW)
		move(data, data->pos_x, data->pos_y - 1);
	else if (key == RIGHT_D || key == RIGHT_ARROW)
		move(data, data->pos_x, data->pos_y + 1);
	else if (key == ESC)
	{
		ft_printf("Cerrando juego\n");
		data_destroyer(data);
	}
	return (1);
}

void	game_init(t_data *data)
{
	int	x;
	int	y;
	int	i;
	int	j;

	ft_printf("Debug: Iniciando game_init\n");
	
	if (!data)
	{
		ft_printf("Error\nEstructura de datos no inicializada\n");
		exit(1);
	}
	
	if (!data->m_map)
	{
		ft_printf("Error\nm_map no inicializado\n");
		exit(1);
	}
	
	if (!data->game_map)
	{
		ft_printf("Error\ngame_map no inicializado\n");
		exit(1);
	}
	
	ft_printf("Debug: Contando cajas colocadas\n");
	data->m_map->boxes_placed = 0;
	i = -1;
	while (data->game_map[++i])
	{
		j = -1;
		while (data->game_map[i][++j])
			if (data->game_map[i][j] == 'B')
				data->m_map->boxes_placed++;
	}
	
	ft_printf("Debug: Inicializando datos del juego\n");
	data->all_placed = (data->m_map->boxes_placed == data->m_map->boxes);
	data->width = data->width * 64;
	data->height = data->height * 64;
	x = data->height + 25;
	y = data->width;
	
	ft_printf("Debug: Inicializando mlx\n");
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_printf("Error\nFallo al iniciar mlx\n");
		exit(1);
	}
	
	ft_printf("Debug: Creando ventana\n");
	data->mlx_window = mlx_new_window(data->mlx, y, x, "Sokoban");
	if (!data->mlx_window)
	{
		ft_printf("Error\nFallo al crear ventana\n");
		exit(1);
	}
	
	ft_printf("Debug: Asignando memoria para imágenes\n");
	data->img = ft_calloc(1, sizeof(t_sprites));
	if (!data->img)
	{
		ft_printf("Error\nFallo de memoria\n");
		exit(1);
	}
	
	ft_printf("Debug: Cargando imágenes\n");
	loading(data, data->img);
	drawing(data);
	find_player(data);
	mlx_hook(data->mlx_window, 2, 1L << 0, keys_press, data);
	mlx_hook(data->mlx_window, X, 0, data_destroyer, data);
	mlx_loop(data->mlx);
}
