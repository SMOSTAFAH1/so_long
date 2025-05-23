/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 12:00:00 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 12:00:00 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_format(char *file)
{
	int		len;
	char	*ext;

	len = ft_strlen(file);
	if (len < 5 || ft_strncmp(&file[len - 4], ".ber", 4))
	{
		ft_printf("Error\nInvalid file format\n");
		return (0);
	}
	ext = ft_strchr(file, '.');
	if (ext == NULL)
	{
		ft_printf("Error\nInvalid file format\n");
		return (0);
	}
	if (ft_strncmp(ext, ".ber", 4) != 0)
		return (0);
	return (1);
}

int	check_argv(int argc, char **argv, t_data *data)
{
	if (argc != 2 || !argv[1])
	{
		ft_printf("Error\nInvalid arguments\n");
		data_destroyer(data);
	}
	if (!check_format(argv[1]))
		data_destroyer(data);
	return (1);
}
