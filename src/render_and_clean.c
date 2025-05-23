/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_and_clean.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 20:32:57 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 20:32:57 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../so_long.h"

void	load_textures(t_game *game)
{
	int	img_width;
	int	img_height;

	game->wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall.xpm", &img_width, &img_height);
	game->floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor.xpm", &img_width, &img_height);
	game->player = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &img_width, &img_height);
	game->collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &img_width, &img_height);
	game->exit = mlx_xpm_file_to_image(game->mlx,
			"textures/exit.xpm", &img_width, &img_height);
}

void	render_map(t_game *game, int x, int y)
{
	void	*img;

	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->floor,
				x * TILE_SIZE, y * TILE_SIZE);
			img = NULL;
			if (game->map[y][x] == '1')
				img = game->wall;
			else if (game->map[y][x] == 'P')
				img = game->player;
			else if (game->map[y][x] == 'C')
				img = game->collectible;
			else if (game->map[y][x] == 'E')
				img = game->exit;
			if (img != NULL)
				mlx_put_image_to_window(game->mlx, game->win, img,
					x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	free_textures(t_game *game)
{
	if (game->wall)
	{
		mlx_destroy_image(game->mlx, game->wall);
		game->wall = NULL;
	}
	if (game->floor)
	{
		mlx_destroy_image(game->mlx, game->floor);
		game->floor = NULL;
	}
	if (game->player)
	{
		mlx_destroy_image(game->mlx, game->player);
		game->player = NULL;
	}
	if (game->collectible)
	{
		mlx_destroy_image(game->mlx, game->collectible);
		game->collectible = NULL;
	}
	if (game->exit)
	{
		mlx_destroy_image(game->mlx, game->exit);
		game->exit = NULL;
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

int	clean_exit(t_game *game)
{
	free_resources(game);
	exit(0);
	return (0);
}
