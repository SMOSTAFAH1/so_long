/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_check_map.c                                    :+:      :+:    :+:   */
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
	data->check = 0;
	flood_fill(data, data->pos_x, data->pos_y);
	if (!data->check)
		return (ft_printf("Error\nNivel imposible de completar\n"), 0);
	data->m_map->boxes = n_boxes;
	data->m_map->targets = n_targets;
	return (1);
}

int	read_map_simple(t_data *data)
{
	char	buffer[4096];
	int		bytes_read;
	int		i;
	int		line_count = 0;
	char	*ptr;
	
	ft_printf("Debug: Reading map from FD: %d\n", data->fd);
	
	// Read the entire file
	bytes_read = read(data->fd, buffer, sizeof(buffer) - 1);
	if (bytes_read <= 0)
	{
		ft_printf("Error\nFailed to read map file or file is empty\n");
		return (0);
	}
	
	buffer[bytes_read] = '\0';
	ft_printf("Debug: Read %d bytes from map file\n", bytes_read);
	
	// Count lines
	ptr = buffer;
	while (*ptr)
	{
		if (*ptr == '\n')
			line_count++;
		ptr++;
	}
	if (*(ptr - 1) != '\n') // If last line doesn't end with a newline
		line_count++;
		
	// Allocate memory for lines
	data->map = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!data->map)
	{
		ft_printf("Error\nFailed to allocate memory for map\n");
		return (0);
	}
	
	// Create a duplicate for game use
	data->game_map = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!data->game_map)
	{
		ft_printf("Error\nFailed to allocate memory for game map\n");
		free(data->map);
		return (0);
	}
	
	// Parse the buffer into lines
	ptr = buffer;
	for (i = 0; i < line_count; i++)
	{
		char *line_start = ptr;
		while (*ptr && *ptr != '\n')
			ptr++;
		
		size_t line_len = ptr - line_start;
		if (*ptr == '\n')
			ptr++;
		
		data->map[i] = (char *)malloc(line_len + 1);
		if (!data->map[i])
		{
			ft_printf("Error\nFailed to allocate memory for map line\n");
			// Cleanup previously allocated lines
			while (--i >= 0)
			{
				free(data->map[i]);
				free(data->game_map[i]);
			}
			free(data->map);
			free(data->game_map);
			return (0);
		}
		
		data->game_map[i] = (char *)malloc(line_len + 1);
		if (!data->game_map[i])
		{
			ft_printf("Error\nFailed to allocate memory for game map line\n");
			free(data->map[i]);
			while (--i >= 0)
			{
				free(data->map[i]);
				free(data->game_map[i]);
			}
			free(data->map);
			free(data->game_map);
			return (0);
		}
		
		ft_memcpy(data->map[i], line_start, line_len);
		data->map[i][line_len] = '\0';
		
		ft_memcpy(data->game_map[i], line_start, line_len);
		data->game_map[i][line_len] = '\0';
	}
	
	data->map[line_count] = NULL;
	data->game_map[line_count] = NULL;
	
	// Verify map content
	ft_printf("Debug: Verifying map\n");
	for (i = 0; data->map[i] != NULL; i++)
		ft_printf("Line %d: %s\n", i, data->map[i]);
	
	// Check map validity
	if (!check_map(data, data->map))
	{
		// Cleanup allocated memory
		for (i = 0; data->map[i] != NULL; i++)
		{
			free(data->map[i]);
			free(data->game_map[i]);
		}
		free(data->map);
		free(data->game_map);
		return (0);
	}
	
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
	if (!read_map_simple(data))
		return (0);
	ft_printf("Debug: Mapa leído correctamente\n");
	return (1);
}
