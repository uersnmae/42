CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Isrcs -O3

VPATH = srcs:srcs/fdf:srcs/hook:srcs/handler:srcs/utils:srcs/key_handle:srcs/img:srcs/matrix:includes/

FDF_INC = fdf.h
FDF_SRC = fdf.c \
		  algebra.c \
		  handle_error.c \
		  handler_key.c \
		  handler_mouse.c \
		  hook_arrow.c \
		  hook_init.c \
		  hook_key.c \
		  hook_mouse.c \
		  img_put_bresenham_line.c \
		  img_put_pixel.c \
		  img_wireframe.c \
		  init_depth.c \
		  model_matrix.c \
		  orthographic_projection.c \
		  rotate_matrix.c \
		  utils_matrix.c \
		  view_matrix.c \
		  parse_map.c \
		  projection.c \

BONUS_INC = fdf_bonus.h
BONUS_SRC = test.c

FDF = fdf 
BONUS = fdf_bonus
NAME = $(FDF) $(BONUS)

OBJ_DIR = obj
LIBFT = libft.a
LIBFT_DIR = libft
LIBFT_FILE = $(LIBFT_DIR)/$(LIBFT)
CFLAGS += -I $(LIBFT_DIR) -I $(LIBFT_DIR)/get_next_line

FT_PRINTF = libftprintf.a
FT_PRINTF_DIR = libft/ft_printf
FT_PRINTF_FILE = $(FT_PRINTF_DIR)/$(FT_PRINTF)
CFLAGS += -I $(FT_PRINTF_DIR)/includes

MLX = libmlx_Linux.a
MLX_REPO = https://github.com/42Paris/minilibx-linux.git
MLX_DIR = minilibx-linux
MLX_FILE = $(MLX_DIR)/$(MLX)
CFLAGS += -I $(MLX_DIR)

LIB = $(LIBFT_FILE) $(FT_PRINTF_FILE) $(MLX_FILE)

FDF_OBJ = $(addprefix $(OBJ_DIR)/, $(FDF_SRC:.c=.o))
BONUS_OBJ = $(addprefix $(OBJ_DIR)/, $(BONUS_SRC:.c=.o))

all: $(FDF)

bonus: $(BONUS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone "$(MLX_REPO)" "$(MLX_DIR)"; \
	fi
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(FDF): $(FDF_OBJ) $(LIB)
	$(CC) $(CFLAGS) $^ -lXext -lX11 -lm -lz -o $@

$(BONUS): $(BONUS_OBJ) $(LIB)
	$(CC) $(CFLAGS) $^ -lXext -lX11 -lm -lz -o $@

$(LIBFT_FILE):
	$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF_FILE):
	$(MAKE) -C $(FT_PRINTF_DIR)

$(MLX_FILE):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(MLX_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(FT_PRINTF_DIR)

fclean: clean
	rm -rf $(FDF) $(BONUS)
	rm -rf $(MLX_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(FT_PRINTF_DIR)

mlx:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone "$(MLX_REPO)" "$(MLX_DIR)"; \
	else \
		echo "MLX exists!!"; \
	fi
re: fclean all

.PHONY: all bonus clean fclean mlx re
