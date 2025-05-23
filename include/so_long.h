/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 12:00:00 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 12:00:00 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../Libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>

# define X 17
# define RIGHT_D 100
# define LEFT_A 97
# define UP_W 119
# define DOWN_S 115
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define ESC 65307

typedef struct s_sprites
{
	void	*player;       /* Jugador */
	void	*wall;         /* Pared */
	void	*floor;        /* Suelo */
	void	*box;          /* Caja */
	void	*target;       /* Objetivo */
	void	*box_on_target; /* Caja en objetivo */
	void	*exit;         /* Salida */
	void	*player_on_target; /* Jugador en objetivo */
}			t_sprites;

typedef struct s_map
{
	int		width;
	int		height;
	int		boxes;       /* Número de cajas */
	int		targets;     /* Número de objetivos */
	int		exit;        /* Salida */
	int		player;      /* Jugador */
	int		boxes_placed; /* Cajas colocadas en objetivos */
}			t_map;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_window;
	int			width;
	int			height;
	int			fd;
	int			moves;
	int			pos_x;
	int			pos_y;
	int			exit_x;
	int			exit_y;
	int			on_target;   /* Indica si el jugador está sobre un objetivo */
	int			all_placed;  /* Indica si todas las cajas están en objetivos */
	int			check;       /* Flag para comprobar validez del mapa */
	char		**map;       /* Mapa original */
	char		**game_map;  /* Mapa para el juego */
	t_sprites	*img;
	t_map		*m_map;
}			t_data;

/* check_argv.c */
int		check_format(char *file);
int		check_argv(int argc, char **argv, t_data *data);

/* check_map.c */
int		wall_surrounded(char **map);
int		is_rectangular(char **map);
int		check_map(t_data *data, char **map);
int		read_map(t_data *data);
int		check(t_data *data, char **argv);

/* tools.c */
void	find_player(t_data *data);
int		game_conditions(t_data *data);
int		available_char(char c);
int		check_items(t_data *data, char **map);
void	flood_fill(t_data *data, int x, int y);

/* tools2.c */
int		check_chars(char **map);
void	update_location(t_data *data, int x, int y);
void	check_exit(t_data *data, int x, int y);
void	push_box(t_data *data, int x, int y, int dir_x, int dir_y);
int		is_box(char c);

/* load_data.c */
void	loading(t_data *data, t_sprites *img);
void	put_image(t_data *data, char flag, int j, int i);
void	drawing(t_data *data);

/* free.c */
void	free_sprites(t_data *data);
void	free_array(char **array1, char **array2);
int		data_destroyer(t_data *data);

/* main.c */
void	move(t_data *data, int x, int y);
int		keys_press(int key, t_data *data);
void	game_init(t_data *data);
int		main(int argc, char **argv);

#endif
