#include "mlx/mlx.h"
#include <stdio.h>

int main()
{
    void *mlx;
    void *img;
    int w, h;
    
    mlx = mlx_init();
    if (!mlx)
    {
        printf("Error: MLX initialization failed\n");
        return 1;
    }
    printf("MLX initialized successfully\n");
    
    img = mlx_xpm_file_to_image(mlx, "textures/box.xpm", &w, &h);
    if (!img)
    {
        printf("Error: Failed to load box.xpm\n");
        return 1;
    }
    printf("Successfully loaded box.xpm (%dx%d)\n", w, h);
    
    return 0;
}
