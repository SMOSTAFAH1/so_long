# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rexposit <rexposit@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 13:52:09 by rexposit          #+#    #+#              #
#    Updated: 2025/03/05 10:00:00 by rexposit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nombre del ejecutable
NAME 	= so_long

# Compilador y flags
CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -I./minilibx-linux

# Librerías necesarias para MiniLibX en Linux
MLX 	= -L./minilibx-linux -lmlx -lXext -lX11

# Archivos fuente de so_long
SRCS 	= so_long.c \
		  map.c \
		  map_utils.c \
		  map_loader.c \
		  render_and_clean.c \
		  util.c \
		  util1.c \
		  util2.c \
		  util3.c \
		  util4.c \

# Convertimos los archivos .c en .o
OBJS	= $(SRCS:.c=.o)

# Regla principal (compila el ejecutable)
all: $(NAME)

# Compilar so_long
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)
	@echo "✅ Compilación completada: $(NAME)"

# Regla para compilar archivos .c en .o
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "🔹 Compilado: $<"

# Eliminar archivos .o
clean:
	@rm -f $(OBJS)
	@echo "🗑 Archivos objeto eliminados."

# Eliminar el ejecutable y los archivos objeto
fclean: clean
	@rm -f $(NAME)
	@echo "🗑 Ejecutable eliminado."

# Recompilar desde cero
re: fclean all