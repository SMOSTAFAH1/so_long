/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 20:32:51 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 20:32:51 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../so_long.h"

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
			img = get_tile_img(game, game->map[y][x]);
			if (img != NULL)
				mlx_put_image_to_window(game->mlx, game->win, img,
					x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
	display_move_counter(game);
}

void	process_map_line(t_game *game, char *line, int y)
{
	int	x;
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (y == 0)
		game->width = ft_strlen(line);
	else if (ft_strlen(line) != (size_t)game->width)
		clean_exit(game, 0);
	game->map[y] = line;
	x = 0;
	while (x < game->width)
	{
		if (line[x] == 'P')
		{
			game->player_x = x;
			game->player_y = y;
		}
		x++;
	}
}

void	validate_map_characters(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] != '0' && game->map[y][x] != '1'
				&& game->map[y][x] != 'P' && game->map[y][x] != 'E'
				&& game->map[y][x] != 'C' && game->map[y][x] != 'X')
				clean_exit(game, 0);
			x++;
		}
		y++;
	}
}

void	count_and_validate_elements(t_game *game)
{
	int	y;
	int	x;
	int	counts[3];

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'P')
				counts[0]++;
			else if (game->map[y][x] == 'E')
				counts[1]++;
			else if (game->map[y][x] == 'C')
				counts[2]++;
			x++;
		}
		y++;
	}
	if (counts[0] != 1 || counts[2] == 0 || counts[1] != 1)
		clean_exit(game, 0);
}

void	check_map_borders(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if ((y == 0 || y == game->height - 1 || x == 0
					|| x == game->width - 1) && game->map[y][x] != '1')
				clean_exit(game, 0);
			x++;
		}
		y++;
	}
}
