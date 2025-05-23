/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 12:00:00 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 12:00:00 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	wall_surrounded(char **map)
{
	int		i;
	int		j;
	int		height;
	int		width;

	i = -1;
	height = 0;
	while (map[height] != NULL)
		height++;
	width = ft_strlen(map[0]);
	while (map[++i] != NULL)
	{
		j = 0;
		if (i == 0 || i == (height - 1))
		{
			while (map[i][j] != '\0')
			{
				if (map[i][j++] != '1')
					return (0);
			}
		}
		if (i > 0 && i < height)
		{
			if (map[i][0] != '1' || map[i][width - 1] != '1')
				return (0);
		}
	}
	return (1);
}

int	is_rectangular(char **map)
{
	int		i;
	size_t	fline;

	i = 0;
	fline = ft_strlen(map[0]);
	while (map[i] != NULL)
	{
		if (fline != ft_strlen(map[i]) || ft_strlen(map[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_map(t_data *data, char **map)
{
	int	n_boxes;
	int	n_targets;

	if (!is_rectangular(map))
		return (ft_printf("Error\nMapa inválido: no rectangular\n"), 0);
	if (!wall_surrounded(map))
		return (ft_printf("Error\nMapa no cerrado por paredes\n"), 0);
	if (!check_items(data, map))
		return (ft_printf("Error\nElementos inválidos en el mapa\n"), 0);
	if (!check_chars(map))
		return (ft_printf("Error\nCaracteres inválidos en el mapa\n"), 0);
	n_boxes = data->m_map->boxes;
	n_targets = data->m_map->targets;
	if (n_boxes != n_targets)
		return (ft_printf("Error\nNúmero de cajas != objetivos\n"), 0);
	data->width = ft_strlen(map[0]);
	data->height = 0;
	while (map[data->height] != NULL)
		data->height++;
	find_player(data);
	flood_fill(data, data->pos_x, data->pos_y);
	if (!game_conditions(data))
		return (ft_printf("Error\nNivel imposible de completar\n"), 0);
	data->m_map->boxes = n_boxes;
	data->m_map->targets = n_targets;
	return (1);
}

int	read_map(t_data *data)
{
	char	*line;
	char	*str_map;
	char	*tmp;

	ft_printf("Debug: Reading map from FD: %d\n", data->fd);
	
	// Start with empty string
	str_map = ft_strdup("");
	if (!str_map)
	{
		ft_printf("Error\nFailed to allocate memory\n");
		return (0);
	}
	
	// Read first line
	line = get_next_line(data->fd);
	if (!line)
	{
		ft_printf("Error\nFailed to read map\n");
		free(str_map);
		return (0);
	}
	
	ft_printf("Debug: First line read: %s", line);
	
	// Read all lines
	while (line != NULL)
	{
		tmp = str_map;
		str_map = ft_strjoin(str_map, line);
		free(tmp);
		free(line);
		
		if (!str_map)
		{
			ft_printf("Error\nFailed to allocate memory for map\n");
			return (0);
		}
		
		line = get_next_line(data->fd);
	}
	
	ft_printf("Debug: Map completely read\n");
	
	// Split map into lines
	data->map = ft_split(str_map, '\n');
	if (!data->map)
	{
		ft_printf("Error\nFailed to split map\n");
		free(str_map);
		return (0);
	}
	
	// Copy map for game use
	data->game_map = ft_split(str_map, '\n');
	if (!data->game_map)
	{
		ft_printf("Error\nFailed to create game map\n");
		free(str_map);
		free_array(data->map, NULL);
		return (0);
	}
	
	free(str_map);
	
	// Check validity of map
	ft_printf("Debug: Verifying map\n");
	if (!check_map(data, data->map))
		return (0);
		
	ft_printf("Debug: Map verified successfully\n");
	return (1);
}

int	check(t_data *data, char **argv)
{
	ft_printf("Debug: Iniciando check\n");
	data->fd = -1;
	
	if (argv[1])
	{
		ft_printf("Debug: Abriendo archivo %s\n", argv[1]);
		data->fd = open(argv[1], O_RDONLY);
	}
	
	if (data->fd < 0)
	{
		ft_printf("Error\nArchivo no encontrado\n");
		return (0);
	}
	ft_printf("Debug: Leyendo mapa\n");
	if (!read_map(data))
		return (0);
	ft_printf("Debug: Mapa leído correctamente\n");
	return (1);
}
