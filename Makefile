NAME		:= so_long
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g3 -I./minilibx-linux
MLX			:= -L./minilibx-linux -lmlx -lXext -lX11
SRCS		:= src/so_long.c src/map.c src/map_utils.c src/map_loader.c src/render_and_clean.c src/util.c \
				src/util1.c src/util2.c src/util3.c src/ft_printf.c
OBJS		:= $(SRCS:.c=.o)
MAKEFLAGS	+= --no-print-directory

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./minilibx-linux
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C ./minilibx-linux clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all