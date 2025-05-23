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
# include <stdio.h>
# include <stdarg.h>
# include "minilibx-linux/mlx.h"
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
	void	*collectible;
	void	*exit;
	int		player_x;
	int		player_y;
}	t_game;

/* map_loader.c */
void	load_map(t_game *game, char *filename);
int		count_map_lines(char *filename);

/* map.c */
void	process_map_line(t_game *game, char *line, int y);
void	validate_map(t_game *game);
void	validate_map_elements(t_game *game, int p_cnt, int e_cnt, int c_cnt);
void	val_map_characters(t_game *game, int *p_cnt, int *e_cnt, int *c_cnt);
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
int		handle_interacts_move(t_game *game, int new_x, int new_y, int *moves);
int		handle_keypress(int key, t_game *game);

/* util.c */
size_t	ft_strlen(const char *s);
char	*ft_strdup(char *src);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

/* util1.c */
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void	ft_free_strs(char **str, char **str2, char **str3);
char	*ft_strjoin2(const char *s1, const char *s2);

/* util2.c */
int		contains_newline(const char *s);
char	*get_before_newline(const char *s);
char	*get_after_newline(const char *s);
void	ft_read_line(int fd, char **keep, char **tmp);

/* util3.c */
char	*ft_parse_line(char **keep, char **tmp);
char	*get_next_line(int fd);
void	ft_putstr(char *str, int *count);
void	ft_putnbr(int nbr, int *count);
int		ft_printf(char const *format, ...);

#endif