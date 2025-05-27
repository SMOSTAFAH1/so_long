/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 20:32:21 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 20:32:21 by shashemi         ###   ########.fr       */
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
	game->player_evolutions[0] = mlx_xpm_file_to_image(game->mlx,
			"textures/player2.xpm", &img_width, &img_height);
	game->player_evolutions[1] = mlx_xpm_file_to_image(game->mlx,
			"textures/player3.xpm", &img_width, &img_height);
	game->player_evolutions[2] = mlx_xpm_file_to_image(game->mlx,
			"textures/player4.xpm", &img_width, &img_height);
	game->player_evolutions[3] = mlx_xpm_file_to_image(game->mlx,
			"textures/player5.xpm", &img_width, &img_height);
	game->player_evolutions[4] = game->player_evolutions[3];
	game->collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &img_width, &img_height);
	game->exit = mlx_xpm_file_to_image(game->mlx,
			"textures/exit.xpm", &img_width, &img_height);
	game->enemy = mlx_xpm_file_to_image(game->mlx,
			"textures/enemy.xpm", &img_width, &img_height);
}

int	count_map_lines(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

void	read_map_lines(t_game *game, int fd, int max_map_lines)
{
	int		y;
	char	*line;

	game->map = malloc(sizeof(char *) * (max_map_lines + 1));
	if (!game->map)
		clean_exit(game, 0);
	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (*line == '\0' || *line == '\n'
			|| (*line == '\r' && *(line + 1) == '\n')
			|| (ft_strlen(line) <= 2 && (line[0] == '\r' || line[0] == '\n')))
		{
			free(line);
			clean_exit(game, 0);
		}
		process_map_line(game, line, y);
		y++;
		line = get_next_line(fd);
	}
	game->height = y;
	game->width = ft_strlen(game->map[0]);
}

void	load_map(t_game *game, char *filename)
{
	int	fd;
	int	max_map_lines;
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || filename[len - 4] != '.' || filename[len - 3] != 'b'
		|| filename[len - 2] != 'e' || filename[len - 1] != 'r')
		clean_exit(game, 0);
	max_map_lines = count_map_lines(filename);
	if (max_map_lines <= 0)
		clean_exit(game, 0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		clean_exit(game, 0);
	read_map_lines(game, fd, max_map_lines);
	close(fd);
	if (!game->map || game->height == 0 || game->width == 0
		|| game->height > 100 || game->width > 100)
		clean_exit(game, 0);
	validate_map_characters(game);
	count_and_validate_elements(game);
	check_map_borders(game);
	if (!is_map_accessible(game))
		clean_exit(game, 0);
}

int	clean_exit(t_game *game, int error)
{
	if (error == 0)
		write(1, "Error\n", 6);
	else if (error == 2)
		write(1, "¡Has tocado un enemigo! ¡Has muerto!\n", 39);
	free_resources(game);
	exit(0);
	return (0);
}
