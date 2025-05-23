#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv) 
{
    if (argc != 2) {
        printf("Usage: %s <map_file>\n", argv[0]);
        return 1;
    }
    
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }
    
    char buffer[BUFFER_SIZE];
    int bytes_read;
    int line_count = 0;
    char *map_data = NULL;
    size_t map_size = 0;
    char **map = NULL;
    
    // Read entire file into a buffer
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
        buffer[bytes_read] = '\0';
        
        // Count lines
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n')
                line_count++;
        }
        
        // Reallocate memory for combined data
        char *new_data = realloc(map_data, map_size + bytes_read + 1);
        if (!new_data) {
            printf("Error: Memory allocation failed\n");
            free(map_data);
            close(fd);
            return 1;
        }
        
        map_data = new_data;
        memcpy(map_data + map_size, buffer, bytes_read + 1);
        map_size += bytes_read;
    }
    
    close(fd);
    
    // If last character is not a newline, we need one more line
    if (map_size > 0 && map_data[map_size - 1] != '\n')
        line_count++;
    
    printf("File read. %d lines found.\n", line_count);
    printf("Map data:\n%s\n", map_data);
    
    // Parse map into lines
    map = malloc((line_count + 1) * sizeof(char*));
    if (!map) {
        printf("Error: Memory allocation failed\n");
        free(map_data);
        return 1;
    }
    
    char *line_start = map_data;
    int line_index = 0;
    
    for (size_t i = 0; i < map_size; i++) {
        if (map_data[i] == '\n' || map_data[i] == '\0') {
            // Calculate line length
            size_t line_len = &map_data[i] - line_start;
            
            // Allocate memory for the line
            map[line_index] = malloc(line_len + 1);
            if (!map[line_index]) {
                printf("Error: Memory allocation failed\n");
                // Free previously allocated memory
                for (int j = 0; j < line_index; j++) {
                    free(map[j]);
                }
                free(map);
                free(map_data);
                return 1;
            }
            
            // Copy line content
            memcpy(map[line_index], line_start, line_len);
            map[line_index][line_len] = '\0';
            
            // Move to next line
            line_start = &map_data[i + 1];
            line_index++;
            
            if (map_data[i] == '\0')
                break;
        }
    }
    
    map[line_index] = NULL;
    
    // Print map line by line
    printf("Map lines:\n");
    for (int i = 0; i < line_index; i++) {
        printf("Line %d: '%s'\n", i, map[i]);
    }
    
    // Clean up
    for (int i = 0; i < line_index; i++) {
        free(map[i]);
    }
    free(map);
    free(map_data);
    
    return 0;
}
