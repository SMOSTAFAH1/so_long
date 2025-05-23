/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:00:53 by rexposit          #+#    #+#             */
/*   Updated: 2025/03/05 01:15:51 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map_validity(t_game *game)
{
	if (!game->map || game->height == 0 || game->width == 0)
	{
		ft_printf("Error: El mapa no puede estar vacío\n");
		clean_exit(game);
	}
	if (game->height > 100)
	{
		ft_printf("Error: El mapa es demasiado alto\n");
		clean_exit(game);
	}
	if (game->width > 100)
	{
		ft_printf("Error: El mapa es demasiado largo\n");
		clean_exit(game);
	}
}

void	flood_fill(char **map, int x, int y, t_game *game)
{
	if (x < 0 || y < 0 || x >= game->width || y >= game->height
		|| map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
}

void	copy_map_and_fill(t_game *game, char ***map_copy)
{
	int	y;

	*map_copy = malloc(sizeof(char *) * (game->height + 1));
	if (!(*map_copy))
		return ;
	y = 0;
	while (y < game->height)
	{
		(*map_copy)[y] = ft_strdup(game->map[y]);
		if (!(*map_copy)[y])
		{
			while (y--)
				free((*map_copy)[y]);
			free(*map_copy);
			*map_copy = NULL;
			return ;
		}
		y++;
	}
	(*map_copy)[y] = NULL;
	flood_fill(*map_copy, game->player_x, game->player_y, game);
}

int	is_map_accessible(t_game *game)
{
	char	**map_copy;
	int		y;
	int		x;
	int		accessible;

	accessible = 1;
	copy_map_and_fill(game, &map_copy);
	if (!map_copy)
		return (0);
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if ((map_copy[y][x] == 'C' || map_copy[y][x] == 'E') && accessible)
				accessible = 0;
			x++;
		}
		free(map_copy[y]);
		y++;
	}
	free(map_copy);
	return (accessible);
}
