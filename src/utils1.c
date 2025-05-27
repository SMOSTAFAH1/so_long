/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-27 07:14:23 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-27 07:14:23 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../so_long.h"

void	display_move_counter(t_game *game)
{
	char	*moves_str;
	char	*display_text;
	int		i;
	int		j;

	moves_str = ft_itoa(game->moves);
	if (!moves_str)
		return ;
	display_text = malloc(sizeof(char) * (12 + ft_strlen(moves_str) + 1));
	if (!display_text)
	{
		free(moves_str);
		return ;
	}
	i = 0;
	j = 0;
	while ("Movimientos: "[i])
		display_text[j++] = "Movimientos: "[i++];
	i = 0;
	while (moves_str[i])
		display_text[j++] = moves_str[i++];
	display_text[j] = '\0';
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, display_text);
	free(moves_str);
	free(display_text);
}

void	*get_tile_img(t_game *game, char tile)
{
	if (tile == '1')
		return (game->wall);
	else if (tile == '0')
		return (game->floor);
	else if (tile == 'P')
		return (get_current_player_texture(game));
	else if (tile == 'C')
		return (game->collectible);
	else if (tile == 'E')
		return (game->exit);
	else if (tile == 'X')
		return (game->enemy);
	return (NULL);
}

void	*get_current_player_texture(t_game *game)
{
	if (game->collected_coins == 0)
		return (game->player);
	else if (game->collected_coins >= 1 && game->collected_coins < 2)
		return (game->player_evolutions[0]);
	else if (game->collected_coins >= 2 && game->collected_coins < 3)
		return (game->player_evolutions[1]);
	else if (game->collected_coins >= 3 && game->collected_coins < 4)
		return (game->player_evolutions[2]);
	else
		return (game->player_evolutions[3]);
}

void	update_player_evolution(t_game *game)
{
	write(1, "¡Has recogido un coleccionable!\n", 33);
	game->collected_coins++;
	if (game->collected_coins == 1)
		write(1, "¡Has evolucionado a Nivel 2!\n", 30);
	else if (game->collected_coins == 2)
		write(1, "¡Has evolucionado a Nivel 3!\n", 30);
	else if (game->collected_coins == 3)
		write(1, "¡Has evolucionado a Nivel 4!\n", 30);
	else if (game->collected_coins == 4)
		write(1, "¡Has evolucionado a Nivel 5 (MÁXIMO)!\n", 40);
	else if (game->collected_coins > 4)
		write(1, "¡Has recogido una moneda! (Ya estás al máximo nivel)\n", 56);
}
