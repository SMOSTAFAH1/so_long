# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 13:52:09 by rexposit          #+#    #+#              #
#    Updated: 2025/03/04 14:24:34 by rexposit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del ejecutable
NAME 	= so_long

# Compilador y flags
CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -I./minilibx-linux -I./Libft

# Librerías necesarias para MiniLibX en Linux
MLX 	= -L./minilibx-linux -lmlx -lXext -lX11

# Archivos fuente de so_long
SRCS 	= so_long.c \
		  map.c \
		  map_utils.c \
		  map_loader.c \
		  render_and_clean.c \

# Directorio de libft
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Convertimos los archivos .c en .o
OBJS	= $(SRCS:.c=.o)

# Regla principal (compila el ejecutable)
all: $(LIBFT) $(NAME)

# Compilar la libft
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Compilar so_long
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "✅ Compilación completada: $(NAME)"

# Regla para compilar archivos .c en .o de so_long
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "🔹 Compilado: $<"

# Eliminar archivos .o
clean:
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)
	@echo "🗑 Archivos objeto eliminados."

# Eliminar el ejecutable y los archivos objeto
fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "🗑 Ejecutable eliminado."

# Recompilar desde cero
re: fclean all