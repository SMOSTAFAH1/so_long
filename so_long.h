/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:42:24 by rexposit          #+#    #+#             */
/*   Updated: 2025/03/04 20:34:50 by rexposit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "minilibx-linux/mlx.h"
# include "Libft/libft.h"
# include <X11/keysym.h>
# include <string.h>

# define TILE_SIZE 64
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

# define KEY_W XK_w
# define KEY_A XK_a
# define KEY_S XK_s
# define KEY_D XK_d
# define KEY_ESC XK_Escape

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		width;
	int		height;
	void	*wall;
	void	*floor;
	void	*player;
	void	*collectible;
	void	*exit;
	int		player_x;
	int		player_y;
}	t_game;

/* map_loader.c */
void	load_map(t_game *game, char *filename);
void	process_map_file(t_game *game, int fd);
int		count_map_lines(char *filename);

/* map.c */
void	process_map_line(t_game *game, char *line, int y);
void	validate_map(t_game *game);
void	validate_map_elements(t_game *game, int p_cnt, int e_cnt, int c_cnt);
void	validate_map_characters(t_game *game, int *p_cnt, int *e_cnt, int *c_cnt);
void	check_collectible_and_border(t_game *game, int x, int y, int *c_cnt);

/* map_utils.c */
void	check_map_validity(t_game *game);
int		is_map_accessible(t_game *game);
void	flood_fill(char **map, int x, int y, t_game *game);
void	copy_map_and_fill(t_game *game, char ***map_copy);

/* render_and_clean.c */
void	render_map(t_game *game, int x, int y);
void	load_textures(t_game *game);
void	free_resources(t_game *game);
void	free_textures(t_game *game);
int		clean_exit(t_game *game);

/* so_long.c */
void	handle_movement(int key, int *new_x, int *new_y, t_game *game);
int		check_remaining_collectibles(t_game *game);
int		handle_interactions_and_move(t_game *game, int new_x, int new_y, int *moves);
int		handle_keypress(int key, t_game *game);

#endif