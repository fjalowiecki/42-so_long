# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjalowie <fjalowie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/13 14:20:27 by fjalowie          #+#    #+#              #
#    Updated: 2024/08/13 18:43:21 by fjalowie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= so_long

SRCS	= src/so_long.c \
		  src/map_validation.c \
		  src/paths_validation.c \
		  src/movement_handling.c \
		  src/elements_drawing.c \
		  src/ft_split.c \
		  src/utils.c

OBJS_DIR = obj
OBJS	= $(patsubst src/%.c, $(OBJS_DIR)/%.o, $(SRCS))

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -I include/
LDFLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

$(OBJS_DIR)/%.o: src/%.c
	@echo "Compiling $<..."
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "Build of $(NAME) completed."

all:	mlx $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJS_DIR)
	@echo "Clean of ${NAME} completed."

fclean: clean
	@rm -f $(NAME)
	@echo "Full clean of ${NAME} completed."

re: fclean all
	@echo "Rebuild of ${NAME} completed."

mlx:
	@if [ ! -d "mlx" ] || [ -z "`ls -A mlx 2>/dev/null`" ]; then \
		echo "Cloning MinilibX repository..."; \
		rm -rf mlx; \
		git clone https://github.com/42Paris/minilibx-linux.git mlx; \
		cd mlx && ./configure > /dev/null 2>&1; \
		echo "MinilibX cloned and configured."; \
	else \
		echo "MinilibX directory already exists and is not empty."; \
	fi

.PHONY: all clean fclean re mlx