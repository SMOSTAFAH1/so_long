/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 20:32:32 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 20:32:32 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../so_long.h"

void	flood_fill(char **map, int x, int y, t_game *game)
{
	if (x < 0 || y < 0 || x >= game->width || y >= game->height
		|| map[y][x] == '1' || map[y][x] == 'F' || map[y][x] == 'X'
		|| map[y][x] == 'E')
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

void	free_textures(t_game *game)
{
	void	**textures[11];
	int		i;

	textures[0] = &game->wall;
	textures[1] = &game->floor;
	textures[2] = &game->player;
	textures[3] = &game->collectible;
	textures[4] = &game->exit;
	textures[5] = &game->enemy;
	textures[6] = &game->player_evolutions[0];
	textures[7] = &game->player_evolutions[1];
	textures[8] = &game->player_evolutions[2];
	textures[9] = &game->player_evolutions[3];
	textures[10] = NULL;
	i = 0;
	while (textures[i])
	{
		if (*textures[i])
		{
			mlx_destroy_image(game->mlx, *textures[i]);
			*textures[i] = NULL;
		}
		i++;
	}
}

void	free_resources(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = -1;
		while (++i < game->height)
		{
			if (game->map[i])
			{
				free(game->map[i]);
				game->map[i] = NULL;
			}
		}
		free(game->map);
		game->map = NULL;
	}
	free_textures(game);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}
