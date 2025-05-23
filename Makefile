# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2025-05-23 12:00:00 by shashemi          #+#    #+#             #
#   Updated: 2025-05-23 12:00:00 by shashemi         ###   ########.fr       #
#                                                                            #
# ************************************************************************** #
NAME        := so_long
CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -g3
AR          := ar rcs
MAKEFLAGS 	+= --no-print-directory

LIBFT_DIR   := Libft
LIBFT_A     := $(LIBFT_DIR)/libft.a
INCLUDES    := include/so_long.h

SRC_DIR     := src
SRCS        := $(SRC_DIR)/check_argv.c \
               $(SRC_DIR)/new_check_map.c \
               $(SRC_DIR)/tools.c \
               $(SRC_DIR)/tools2.c \
               $(SRC_DIR)/load_data_simple.c \
               $(SRC_DIR)/free.c \
               $(SRC_DIR)/main.c
OBJS        := $(SRCS:.c=.o)

MAIN_SRC    := main.c
MAIN_OBJ    := $(MAIN_SRC:.c=.o)

.PHONY: all clean fclean re bonus

all: $(NAME)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR) bonus

MLX_DIR     := mlx
MLX_A       := $(MLX_DIR)/libmlx.a
MLX_FLAGS   := -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm

$(MLX_A):
	@$(MAKE) -C $(MLX_DIR)

$(MAIN_OBJ): $(MAIN_SRC)
	@echo "Compilando $(MAIN_SRC)"
	@$(CC) $(CFLAGS) -I include -I $(MLX_DIR) -c $< -o $@

$(NAME): $(LIBFT_A) $(MLX_A) $(OBJS) $(MAIN_OBJ)
	@echo "Compilando $@"
	@$(CC) $(CFLAGS) -I include -I $(MLX_DIR) $(MAIN_OBJ) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "¡Compilación completada!"

%.o: %.c $(INCLUDES)
	@echo "Compilando $<"
	@$(CC) $(CFLAGS) -I include -I $(MLX_DIR) -c $< -o $@

clean:
	@echo "Limpiando archivos objeto"
	@rm -f $(OBJS) $(MAIN_OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@echo "Limpiando ejecutable"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus: all