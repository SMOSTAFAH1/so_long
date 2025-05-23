/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 20:33:03 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 20:33:03 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../so_long.h"

void	handle_movement(int key, int *new_x, int *new_y, t_game *game)
{
	*new_x = game->player_x;
	*new_y = game->player_y;
	if (key == KEY_W)
		(*new_y)--;
	else if (key == KEY_S)
		(*new_y)++;
	else if (key == KEY_A)
		(*new_x)--;
	else if (key == KEY_D)
		(*new_x)++;
	else if (key == KEY_ESC)
		clean_exit(game);
}

int	check_remaining_collectibles(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'C')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	handle_interacts_move(t_game *game, int new_x, int new_y, int *moves)
{
	char	next_pos;

	next_pos = game->map[new_y][new_x];
	if (next_pos == '1')
		return (0);
	else if (next_pos == 'C')
		ft_printf("¡Coleccionable recogido!\n");
	else if (next_pos == 'E')
	{
		if (check_remaining_collectibles(game))
		{
			ft_printf("¡Aún quedan coleccionables por recoger!\n");
			return (0);
		}
		ft_printf("¡Has ganado!\n");
		clean_exit(game);
	}
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	(*moves)++;
	ft_printf("Movimientos: %d\n", *moves);
	render_map(game, 0, 0);
	return (1);
}

int	handle_keypress(int key, t_game *game)
{
	static int	moves;
	int			new_x;
	int			new_y;

	if (key != KEY_W && key != KEY_A && key != KEY_S
		&& key != KEY_D && key != KEY_ESC)
		return (0);
	handle_movement(key, &new_x, &new_y, game);
	handle_interacts_move(game, new_x, new_y, &moves);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	if (argc != 2)
	{
		ft_printf("Uso: %s <mapa.ber>\n", argv[0]);
		return (1);
	}
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		ft_printf("Error: No se pudo inicializar MLX\n");
		clean_exit(&game);
	}
	load_map(&game, argv[1]);
	game.win = mlx_new_window(game.mlx, game.width * TILE_SIZE,
			game.height * TILE_SIZE, "so_long");
	load_textures(&game);
	render_map(&game, 0, 0);
	mlx_key_hook(game.win, handle_keypress, &game);
	mlx_hook(game.win, 17, 0L, clean_exit, &game);
	mlx_loop(game.mlx);
	return (0);
}
