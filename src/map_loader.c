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
		clean_exit(game);
	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (*line == '\0')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
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

	max_map_lines = count_map_lines(filename);
	if (max_map_lines <= 0)
	{
		ft_printf("Error: El mapa no puede estar vacío\n");
		clean_exit(game);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		clean_exit(game);
	read_map_lines(game, fd, max_map_lines);
	close(fd);
	validate_map(game);
}

void	free_map(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = 0;
		while (i < game->height)
		{
			if (game->map[i])
			{
				free(game->map[i]);
				game->map[i] = NULL;
			}
			i++;
		}
		free(game->map);
		game->map = NULL;
	}
}
