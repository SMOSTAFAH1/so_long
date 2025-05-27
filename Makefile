NAME		:= so_long
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g3 -I./minilibx-linux
MLX			:= -L./minilibx-linux -lmlx -lXext -lX11
SRCS		:= src/so_long.c src/gnl.c src/map.c src/utils.c src/map_utils.c src/map_loader.c src/utils1.c
BONUS		:= src/so_long.c src/gnl.c src/map.c src/utils.c src/map_utils.c src/map_loader.c src/utils1.c
OBJS		:= $(SRCS:.c=.o)
BONUS_OBJS	:= $(BONUS:.c=.o)
MAKEFLAGS	+= --no-print-directory

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./minilibx-linux
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C ./minilibx-linux clean
	rm -f $(OBJS) $(BONUS_OBJS) .bonus

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: .bonus

.bonus: $(BONUS_OBJS)
	make -C ./minilibx-linux
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(MLX) -o $(NAME)
	@touch .bonus