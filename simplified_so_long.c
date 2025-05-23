/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplified_so_long.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-23 12:00:00 by shashemi          #+#    #+#             */
/*   Updated: 2025-05-23 12:00:00 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "mlx/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>

#define BUFFER_SIZE 1024
#define TILE_SIZE 64

// Key codes
#define ESC 65307
#define UP_W 119
#define DOWN_S 115
#define LEFT_A 97
#define RIGHT_D 100
#define UP_ARROW 65362
#define DOWN_ARROW 65364
#define LEFT_ARROW 65361
#define RIGHT_ARROW 65363

// Game structures
typedef struct s_sprite {
    void *img;
    int width;
    int height;
} t_sprite;

typedef struct s_game {
    void *mlx;
    void *win;
    char **map;
    int width;
    int height;
    int player_x;
    int player_y;
    int moves;
    int collectibles;
    int collected;
    t_sprite player;
    t_sprite wall;
    t_sprite floor;
    t_sprite collectible;
    t_sprite exit;
    t_sprite target;
} t_game;

// Function prototypes
void load_sprites(t_game *game);
void render_map(t_game *game);
int key_press(int keycode, t_game *game);
int close_window(t_game *game);
void free_resources(t_game *game);

// Load sprites from XPM files
void load_sprites(t_game *game)
{
    game->player.img = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm", 
                                            &game->player.width, &game->player.height);
    game->wall.img = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", 
                                          &game->wall.width, &game->wall.height);
    game->floor.img = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm", 
                                           &game->floor.width, &game->floor.height);
    game->collectible.img = mlx_xpm_file_to_image(game->mlx, "textures/box.xpm", 
                                                 &game->collectible.width, &game->collectible.height);
    game->exit.img = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", 
                                          &game->exit.width, &game->exit.height);
    game->target.img = mlx_xpm_file_to_image(game->mlx, "textures/target.xpm", 
                                            &game->target.width, &game->target.height);
}

// Draw the game map
void render_map(t_game *game)
{
    for (int y = 0; y < game->height; y++)
    {
        for (int x = 0; x < game->width; x++)
        {
            // Always draw floor first
            mlx_put_image_to_window(game->mlx, game->win, game->floor.img, 
                                   x * TILE_SIZE, y * TILE_SIZE);
            
            // Then draw the appropriate element
            switch (game->map[y][x])
            {
                case '1': // Wall
                    mlx_put_image_to_window(game->mlx, game->win, game->wall.img, 
                                           x * TILE_SIZE, y * TILE_SIZE);
                    break;
                case 'P': // Player
                    mlx_put_image_to_window(game->mlx, game->win, game->player.img, 
                                           x * TILE_SIZE, y * TILE_SIZE);
                    break;
                case 'C': // Collectible (box)
                    mlx_put_image_to_window(game->mlx, game->win, game->collectible.img, 
                                           x * TILE_SIZE, y * TILE_SIZE);
                    break;
                case 'E': // Exit
                    mlx_put_image_to_window(game->mlx, game->win, game->exit.img, 
                                           x * TILE_SIZE, y * TILE_SIZE);
                    break;
                case 'X': // Target
                    mlx_put_image_to_window(game->mlx, game->win, game->target.img, 
                                           x * TILE_SIZE, y * TILE_SIZE);
                    break;
            }
        }
    }
}

// Handle key press events
int key_press(int keycode, t_game *game)
{
    int new_x = game->player_x;
    int new_y = game->player_y;
    
    // Determine new position based on key press
    if (keycode == UP_W || keycode == UP_ARROW)
        new_y--;
    else if (keycode == DOWN_S || keycode == DOWN_ARROW)
        new_y++;
    else if (keycode == LEFT_A || keycode == LEFT_ARROW)
        new_x--;
    else if (keycode == RIGHT_D || keycode == RIGHT_ARROW)
        new_x++;
    else if (keycode == ESC)
        close_window(game);
    
    // Check if move is valid
    if (game->map[new_y][new_x] != '1')
    {
        // Handle collectibles
        if (game->map[new_y][new_x] == 'C')
        {
            game->collected++;
            game->map[new_y][new_x] = '0'; // Replace collectible with empty space
        }
        // Handle exit
        else if (game->map[new_y][new_x] == 'E')
        {
            if (game->collected == game->collectibles)
            {
                printf("You win! Total moves: %d\n", game->moves + 1);
                close_window(game);
            }
            else
            {
                printf("Collect all boxes first!\n");
                return (0);
            }
        }
        
        // Update player position
        game->map[game->player_y][game->player_x] = '0'; // Old position becomes empty
        game->map[new_y][new_x] = 'P'; // New position has player
        game->player_x = new_x;
        game->player_y = new_y;
        game->moves++;
        
        // Render updated map
        render_map(game);
        printf("Moves: %d\n", game->moves);
    }
    
    return (0);
}

// Handle window close
int close_window(t_game *game)
{
    free_resources(game);
    exit(0);
    return (0);
}

// Free allocated resources
void free_resources(t_game *game)
{
    // Free map
    if (game->map)
    {
        for (int i = 0; i < game->height; i++)
            free(game->map[i]);
        free(game->map);
    }
    
    // Free sprites
    if (game->mlx)
    {
        if (game->player.img)
            mlx_destroy_image(game->mlx, game->player.img);
        if (game->wall.img)
            mlx_destroy_image(game->mlx, game->wall.img);
        if (game->floor.img)
            mlx_destroy_image(game->mlx, game->floor.img);
        if (game->collectible.img)
            mlx_destroy_image(game->mlx, game->collectible.img);
        if (game->exit.img)
            mlx_destroy_image(game->mlx, game->exit.img);
        if (game->target.img)
            mlx_destroy_image(game->mlx, game->target.img);
        
        // Close window and free MLX
        if (game->win)
            mlx_destroy_window(game->mlx, game->win);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
}

// Read map from file
int read_map(t_game *game, char *file_path)
{
    int fd;
    char buffer[BUFFER_SIZE];
    int bytes_read;
    int line_count = 0;
    char *map_data = NULL;
    size_t map_size = 0;
    
    // Open map file
    fd = open(file_path, O_RDONLY);
    if (fd < 0)
    {
        printf("Error: Could not open file %s\n", file_path);
        return (0);
    }
    
    // Read entire file into a buffer
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0)
    {
        buffer[bytes_read] = '\0';
        
        // Count lines
        for (int i = 0; i < bytes_read; i++)
        {
            if (buffer[i] == '\n')
                line_count++;
        }
        
        // Allocate/reallocate memory for map data
        char *new_data = realloc(map_data, map_size + bytes_read + 1);
        if (!new_data)
        {
            printf("Error: Memory allocation failed\n");
            free(map_data);
            close(fd);
            return (0);
        }
        
        map_data = new_data;
        memcpy(map_data + map_size, buffer, bytes_read + 1);
        map_size += bytes_read;
    }
    
    close(fd);
    
    // If last character is not a newline, add one more line
    if (map_size > 0 && map_data[map_size - 1] != '\n')
        line_count++;
    
    game->height = line_count;
    
    // Parse map into lines
    game->map = malloc((line_count + 1) * sizeof(char*));
    if (!game->map)
    {
        printf("Error: Memory allocation failed\n");
        free(map_data);
        return (0);
    }
    
    char *line_start = map_data;
    int line_index = 0;
    size_t line_len;
    
    // Initialize collectibles count
    game->collectibles = 0;
    
    for (size_t i = 0; i <= map_size; i++)
    {
        if (i == map_size || map_data[i] == '\n')
        {
            // Calculate line length
            line_len = &map_data[i] - line_start;
            
            // Set map width based on first line
            if (line_index == 0)
                game->width = line_len;
            else if (line_len != (size_t)game->width)
            {
                printf("Error: Map is not rectangular\n");
                for (int j = 0; j < line_index; j++)
                    free(game->map[j]);
                free(game->map);
                free(map_data);
                return (0);
            }
            
            // Allocate memory for the line
            game->map[line_index] = malloc(line_len + 1);
            if (!game->map[line_index])
            {
                printf("Error: Memory allocation failed\n");
                for (int j = 0; j < line_index; j++)
                    free(game->map[j]);
                free(game->map);
                free(map_data);
                return (0);
            }
            
            // Copy line content
            memcpy(game->map[line_index], line_start, line_len);
            game->map[line_index][line_len] = '\0';
            
            // Count collectibles and find player position
            for (size_t j = 0; j < line_len; j++)
            {
                if (game->map[line_index][j] == 'C')
                    game->collectibles++;
                else if (game->map[line_index][j] == 'P')
                {
                    game->player_x = j;
                    game->player_y = line_index;
                }
            }
            
            // Move to next line
            line_start = &map_data[i + 1];
            line_index++;
            
            if (i == map_size)
                break;
        }
    }
    
    game->map[line_index] = NULL;
    game->collected = 0;
    game->moves = 0;
    
    // Clean up
    free(map_data);
    
    return (1);
}

// Main function
int main(int argc, char **argv)
{
    t_game game;
    
    // Check arguments
    if (argc != 2)
    {
        printf("Usage: %s <map_file>\n", argv[0]);
        return (1);
    }
    
    // Initialize game structure
    memset(&game, 0, sizeof(t_game));
    
    // Read map from file
    if (!read_map(&game, argv[1]))
        return (1);
    
    // Initialize MLX
    game.mlx = mlx_init();
    if (!game.mlx)
    {
        printf("Error: Failed to initialize MLX\n");
        free_resources(&game);
        return (1);
    }
    
    // Create window
    game.win = mlx_new_window(game.mlx, game.width * TILE_SIZE, game.height * TILE_SIZE, "Sokoban");
    if (!game.win)
    {
        printf("Error: Failed to create window\n");
        free_resources(&game);
        return (1);
    }
    
    // Load sprites
    load_sprites(&game);
    
    // Initial render
    render_map(&game);
    
    // Set up hooks
    mlx_hook(game.win, 2, 1L << 0, key_press, &game); // Key press
    mlx_hook(game.win, 17, 0L, close_window, &game);  // Window close
    
    // Start game loop
    mlx_loop(game.mlx);
    
    return (0);
}
