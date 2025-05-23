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

void	process_map_line(t_game *game, char *line, int y)
{
	int	x;
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (y == 0)
		game->width = ft_strlen(line);
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

void	check_collectible_and_border(t_game *game, int x, int y, int *c_cnt)
{
	if (game->map[y][x] == 'C')
		(*c_cnt)++;
	if ((y == 0 || y == game->height - 1 || x == 0 || x == game->width - 1)
		&& game->map[y][x] != '1')
	{
		ft_printf("Error: El mapa debe estar cerrado con paredes\n");
		free_resources(game);
		exit(1);
	}
}

void	val_map_characters(t_game *game, int *p_cnt,
	int *e_cnt, int *c_cnt)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'P')
				(*p_cnt)++;
			else if (game->map[y][x] == 'E')
				(*e_cnt)++;
			else if (game->map[y][x] == 'C')
				(*c_cnt)++;
			else if (game->map[y][x] == ' ')
			{
				ft_printf("Error: El mapa contiene espacios vacíos\n");
				clean_exit(game);
			}
			check_collectible_and_border(game, x, y, c_cnt);
			x++;
		}
		y++;
	}
}

void	validate_map_elements(t_game *game, int p_cnt, int e_cnt, int c_cnt)
{
	if (p_cnt != 1)
	{
		ft_printf("Error: El mapa debe tener exactamente 1 jugador ('P')\n");
		clean_exit(game);
	}
	if (e_cnt == 0)
	{
		ft_printf("Error: El mapa debe tener al menos una salida ('E')\n");
		clean_exit(game);
	}
	if (c_cnt == 0)
	{
		ft_printf("Error: El mapa debe tener al menos 1 coleccionable ('C')\n");
		clean_exit(game);
	}
}

void	validate_map(t_game *game)
{
	int	p_cnt;
	int	e_cnt;
	int	c_cnt;

	p_cnt = 0;
	e_cnt = 0;
	c_cnt = 0;
	check_map_validity(game);
	val_map_characters(game, &p_cnt, &e_cnt, &c_cnt);
	validate_map_elements(game, p_cnt, e_cnt, c_cnt);
	if (!is_map_accessible(game))
	{
		ft_printf("Error: La salida o los coleccionables no son accesibles\n");
		clean_exit(game);
	}
}
