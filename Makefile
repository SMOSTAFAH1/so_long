# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2025-05-06 07:24:11 by shashemi          #+#    #+#             #
#   Updated: 2025-05-06 07:24:11 by shashemi         ###   ########.fr       #
#                                                                            #
# ************************************************************************** #
NAME        := so_long
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g3
AR          := ar rcs
MAKEFLAGS 	+= --no-print-directory

LIBFT_DIR   := Libft
LIBFT_A     := $(LIBFT_DIR)/libft.a
INCLUDES    := so_long.h

SRCS        := main.c
OBJS        := $(SRCS:.c=.o)

.PHONY: all clean fclean re bonus

all: $(NAME)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all