# Project name
NAME = cub3D

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
# LIBX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -O3

# Source files
SRC_DIR = srcs
SRCS = main.c \
	   check_map.c \
	   check_player.c \
	   init.c \
	   init_metadata.c \
	   init_map.c \
	   utils.c \
	   gnl/get_next_line.c \
	   gnl/get_next_line_utils.c \
	   libft/ft_atoi.c \
	   libft/ft_bzero.c \
	   libft/ft_calloc.c \
	   libft/ft_isdigit.c \
	   libft/ft_isspace.c \
	   libft/ft_memcpy.c \
	   libft/ft_memset.c \
	   libft/ft_putstr_fd.c \
	   libft/ft_split.c \
	   libft/ft_strchr.c \
	   libft/ft_strcmp.c \
	   libft/ft_strdup.c \
	   libft/ft_strlen.c \
	   libft/ft_substr.c \
	#    load_file.c \
	#    check_file.c \
	#    parse_metadata.c \
	#    parse_metadata_utils.c \
	#    parse.c \
	#    parse_map.c \
	#    debug.c \
	#    check_content.c \
	#    check_map.c \
	#    check_map2.c \
	#    init_mlx.c \
	#    textures.c \
	#    free.c \
	#    exit.c \
	#    movement.c \
	#    events.c \
	#    dda_utils.c \
	#    raycast.c \
	#    render.c \
	#    3d_map.c \
	#    2d_map.c \
	#    libft/ft_noprintchar.c \
	#    libft/ft_putspace.c \
	#    libft/ft_strarr_size.c \
	#    libft/ft_strcmp.c \
	#    libft/ft_strlcpy.c \
	#    libft/ft_strtrim.c \


# Minilibx configuration
MLX_PATH	=	minilibx-linux/
MLX_NAME	=	libmlx.a
MLX			=	$(MLX_PATH)$(MLX_NAME)

# Object files
OBJ_DIR = objs
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Header files
INCS = -I includes
# INCS = -I includes -I$(MLX_PATH)

# Color
GREEN = \033[38;5;082;1m
END = \033[0m

.PHONY: all clean fclean re

all: $(NAME)
# all: $(MLX) $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Compiling $(NAME)...$(END)"
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
# @$(CC) $(OBJS) $(CFLAGS) $(LIBX_FLAGS) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/libft
	@mkdir -p $(OBJ_DIR)/gnl

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# Build MiniLibX
$(MLX):
			$(MAKE) -C $(MLX_PATH)

clean:
	@echo "$(GREEN)Removing object files...$(END)"
	@rm -rf $(OBJ_DIR)
# @make -C $(MLX_PATH) clean

fclean: clean
	@echo "$(GREEN)Removeing $(NAME)...$(END)"
	@rm -rf $(NAME)

re : fclean all