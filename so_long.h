/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 20:12:07 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 20:12:07 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>

# define TILE_SIZE 64

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

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
	void	*player_evolutions[5];
	void	*collectible;
	void	*exit;
	int		player_x;
	int		player_y;
	int		moves;
	int		collected_coins;
	void	*enemy;
}	t_game;

void	validate_map_characters(t_game *game);
void	count_and_validate_elements(t_game *game);
void	load_map(t_game *game, char *filename);
void	process_map_line(t_game *game, char *line, int y);
void	check_map_borders(t_game *game);
int		is_map_accessible(t_game *game);
void	render_map(t_game *game, int x, int y);
void	load_textures(t_game *game);
void	free_resources(t_game *game);
int		clean_exit(t_game *game, int error);
size_t	ft_strlen(const char *s);
void	ft_putnbr_fd(int nb, int fd);
char	*ft_strdup(char *src);
char	*get_next_line(int fd);
char	*ft_itoa(int n);
void	display_move_counter(t_game *game);
void	*get_tile_img(t_game *game, char tile);
void	update_player_evolution(t_game *game);
void	*get_current_player_texture(t_game *game);

#endif