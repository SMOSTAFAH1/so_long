#include "../include/so_long.h"

void    create_colored_image(t_data *data, void **img, int color)
{
        char    *data_ptr;
        int     i;
        int     j;
        int     bpp, size_line, endian;
        
        *img = mlx_new_image(data->mlx, 64, 64);
        if (!*img)
                return;
        data_ptr = mlx_get_data_addr(*img, &bpp, &size_line, &endian);
        for (i = 0; i < 64; i++)
        {
                for (j = 0; j < 64; j++)
                {
                        *(int*)(data_ptr + (i * size_line + j * (bpp / 8))) = color;
                }
        }
}

void    loading(t_data *data, t_sprites *img)
{
        ft_printf("Debug: Creating colored images instead of loading XPM\n");
        
        // Create colored rectangles instead of loading XPM files
        create_colored_image(data, &img->wall, 0x8B4513);      // Brown for walls
        create_colored_image(data, &img->floor, 0xF5DEB3);     // Wheat for floor
        create_colored_image(data, &img->box, 0xD2691E);       // Chocolate for box
        create_colored_image(data, &img->player, 0x0000FF);    // Blue for player
        create_colored_image(data, &img->target, 0xFF0000);    // Red for target
        create_colored_image(data, &img->box_on_target, 0x800080); // Purple for box on target
        create_colored_image(data, &img->exit, 0x00FF00);      // Green for exit
        create_colored_image(data, &img->player_on_target, 0x00FFFF); // Cyan for player on target
        
        // Check if all images were created successfully
        if (!img->wall || !img->floor || !img->box || !img->player || 
            !img->target || !img->box_on_target || !img->exit || !img->player_on_target)
        {
                ft_printf("Error\nFallo al crear imágenes de colores\n");
                data_destroyer(data);
        }
        
        ft_printf("Debug: All colored images created successfully\n");
}

void    put_image(t_data *data, char flag, int j, int i)
{
        if (flag == '1')
                mlx_put_image_to_window(data->mlx, data->mlx_window,
                        data->img->wall, j * 64, i * 64);
        else if (flag == '0')
                mlx_put_image_to_window(data->mlx, data->mlx_window,
                        data->img->floor, j * 64, i * 64);
        else if (flag == 'C')
                mlx_put_image_to_window(data->mlx, data->mlx_window,
                        data->img->box, j * 64, i * 64);
        else if (flag == 'P')
                mlx_put_image_to_window(data->mlx, data->mlx_window,
                        data->img->player, j * 64, i * 64);
        else if (flag == 'E')
                mlx_put_image_to_window(data->mlx, data->mlx_window,
                        data->img->exit, j * 64, i * 64);
        else if (flag == 'X')
                mlx_put_image_to_window(data->mlx, data->mlx_window,
                        data->img->target, j * 64, i * 64);
        else if (flag == 'B')
                mlx_put_image_to_window(data->mlx, data->mlx_window,
                        data->img->box_on_target, j * 64, i * 64);
        else if (flag == 'G')
                mlx_put_image_to_window(data->mlx, data->mlx_window,
                        data->img->player_on_target, j * 64, i * 64);
}

void    drawing(t_data *data)
{
        int     i;
        int     j;
        i = 0;
        while (data->game_map[i])
        {
                j = 0;
                while (data->game_map[i][j])
                {
                        if (data->game_map[i][j] == '1')
                                put_image(data, '1', j, i);
                        else if (data->game_map[i][j] == '0')
                                put_image(data, '0', j, i);
                        else if (data->game_map[i][j] == 'C')
                                put_image(data, 'C', j, i);
                        else if (data->game_map[i][j] == 'P')
                                put_image(data, 'P', j, i);
                        else if (data->game_map[i][j] == 'E')
                                put_image(data, 'E', j, i);
                        else if (data->game_map[i][j] == 'X')
                                put_image(data, 'X', j, i);
                        else if (data->game_map[i][j] == 'B')
                                put_image(data, 'B', j, i);
                        else if (data->game_map[i][j] == 'G')
                                put_image(data, 'G', j, i);
                        j++;
                }
                i++;
        }
}
