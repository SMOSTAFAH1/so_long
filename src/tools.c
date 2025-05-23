/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 12:00:00 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 12:00:00 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	find_player(t_data *data)
{
	int	i;
	int	j;

	ft_printf("Debug: Finding player position\n");
	
	if (!data || !data->map)
	{
		ft_printf("Error: Invalid data in find_player\n");
		exit(1);
	}
	
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] == 'P' || data->map[i][j] == 'G')
			{
				data->pos_x = i;
				data->pos_y = j;
				ft_printf("Debug: Player found at position %d,%d\n", i, j);
				return ;
			}
			j++;
		}
		i++;
	}
	
	ft_printf("Error: No player found in the map!\n");
}

int	game_conditions(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] == 'E' || data->map[i][j] == 'C' || 
				data->map[i][j] == 'X')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	available_char(char c)
{
	char	*available;

	available = "01PECXBG";
	if (ft_strchr(available, c) == NULL)
	{
		ft_printf("Debug: Invalid character found: %c\n", c);
		return (0);
	}
	return (1);
}

int	check_items(t_data *data, char **map)
{
	int	i;
	int	j;

	i = -1;
	data->m_map = ft_calloc(1, sizeof(t_map));
	if (data->m_map == NULL)
		return (0);
	
	// Initialize all counts to 0
	data->m_map->boxes = 0;
	data->m_map->targets = 0;
	data->m_map->exit = 0;
	data->m_map->player = 0;
	data->m_map->boxes_placed = 0;
	
	while (map[++i])
	{
		j = -1;
		while (map[i][++j] != '\0')
		{
			if (map[i][j] == 'C' || map[i][j] == 'B')
				data->m_map->boxes++;
			else if (map[i][j] == 'X' || map[i][j] == 'B')
				data->m_map->targets++;
			else if (map[i][j] == 'E')
				data->m_map->exit++;
			else if (map[i][j] == 'P' || map[i][j] == 'G')
				data->m_map->player++;
		}
	}
	
	ft_printf("Debug: Map contains: Player: %d, Boxes: %d, Targets: %d, Exit: %d\n", 
		data->m_map->player, data->m_map->boxes, data->m_map->targets, data->m_map->exit);
	
	if (data->m_map->player == 1 && data->m_map->boxes >= 1 
		&& data->m_map->exit == 1 && data->m_map->targets >= 1)
		return (1);
	return (0);
}

void	flood_fill(t_data *data, int x, int y)
{
	// Check boundaries to avoid segmentation fault
	if (x < 0 || y < 0 || x >= data->height || y >= data->width)
		return;
		
	// Check if cell is already visited or is a wall or box
	if (data->map[x][y] == '1' || data->map[x][y] == 'V'
		|| data->map[x][y] == 'C' || data->map[x][y] == 'B')
		return;
		
	// Target found, decrement counter
	if (data->map[x][y] == 'X')
	{
		ft_printf("Debug: Target found at %d,%d during flood fill\n", x, y);
		data->m_map->targets--;
	}
	
	// Exit found, mark as accessible
	if (data->map[x][y] == 'E')
	{
		ft_printf("Debug: Exit found at %d,%d during flood fill\n", x, y);
		data->check = 1;
		data->map[x][y] = 'V';
		return;
	}
	
	// Mark current cell as visited
	data->map[x][y] = 'V';
	
	// Explore in all four directions
	flood_fill(data, x + 1, y);
	flood_fill(data, x - 1, y);
	flood_fill(data, x, y + 1);
	flood_fill(data, x, y - 1);
}
