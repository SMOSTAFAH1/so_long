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

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*bp;

	i = 0;
	bp = (unsigned char *)b;
	while (i < len)
	{
		bp[i] = (unsigned char)c;
		i++;
	}
	return (b);
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
			{
				write(1, "¡Aún quedan coleccionables por recoger!\n", 42);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	handle_interacts_move(t_game *game, int new_x, int new_y)
{
	char	next_pos;

	next_pos = game->map[new_y][new_x];
	if (next_pos == '1')
		return (0);
	else if (next_pos == 'X')
		clean_exit(game, 2);
	else if (next_pos == 'C')
		update_player_evolution(game);
	else if (next_pos == 'E')
	{
		if (check_remaining_collectibles(game))
			return (0);
		write(1, "¡Has ganado!\n", 14);
		clean_exit(game, 1);
	}
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	render_map(game, 0, 0);
	return (1);
}

int	handle_keypress(int key, t_game *game)
{
	int	new_x;
	int	new_y;

	if (key != XK_w && key != XK_a && key != XK_s
		&& key != XK_d && key != XK_Escape && key != XK_Up
		&& key != XK_Down && key != XK_Left && key != XK_Right)
		return (0);
	if (key == XK_Escape)
		clean_exit(game, 1);
	new_x = game->player_x;
	new_y = game->player_y;
	if (key == XK_w || key == XK_Up)
		new_y--;
	else if (key == XK_s || key == XK_Down)
		new_y++;
	else if (key == XK_a || key == XK_Left)
		new_x--;
	else if (key == XK_d || key == XK_Right)
		new_x++;
	handle_interacts_move(game, new_x, new_y);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	game.mlx = mlx_init();
	if (!game.mlx)
		clean_exit(&game, 0);
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
