/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 12:00:00 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 12:00:00 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	ft_printf("Debug: Starting main function\n");
	
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
	{
		ft_printf("Error\nFailed to allocate memory for game data\n");
		return (0);
	}
	
	ft_printf("Debug: Checking arguments\n");
	if (!check_argv(argc, argv, data))
	{
		ft_printf("Debug: Arguments check failed\n");
		return (data_destroyer(data));
	}
	
	ft_printf("Debug: Checking map\n");
	if (!check(data, argv))
	{
		ft_printf("Debug: Map check failed\n");
		return (data_destroyer(data));
	}
	
	ft_printf("Debug: Initializing game\n");
	game_init(data);
	
	ft_printf("Debug: Game loop finished\n");
	return (data_destroyer(data));
}

