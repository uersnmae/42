CC = cc
DIR = -Iparser -Iutils -Igame -Iloop -Iraycast
CFLAGS = -Wall -Wextra -Werror $(DIR) -g

VPATH = parser:game:loop:utils:libft:raycast

PARSER = parse_dispatch.c \
		parse_map.c \
		parse_rgb.c \
		parse_tex.c \
		parse_utils.c \
		parse_validator.c \
		parser.c \

GAME =  \
	   game_free.c \
	   game_init.c \
	   game_utils.c \
	   init_textures.c \
	   player_update.c \
	   draw_background.c \

LOOP = hooks.c \
	   init_mlx.c \
	   main_loop.c \
	   frame_limit.c \

RAYCAST = dda.c \
		  raycast.c \

UTILS = utils.c

MANDATORY_SRC = cub3D.c $(PARSER) $(UTILS) $(GAME) $(LOOP) $(RAYCAST)

BONUS_SRC = cub3D.c $(PARSER) $(UTILS) $(GAME) $(LOOP) $(RAYCAST) \

MANDATORY = cub3D
BONUS = cub3D_bonus

NAME = $(MANDATORY) $(BONUS)

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

MANDATORY_OBJ = $(addprefix $(OBJ_DIR)/, $(MANDATORY_SRC:.c=.o))
BONUS_OBJ = $(addprefix $(OBJ_DIR)/, $(BONUS_SRC:.c=.o))

all: $(MANDATORY)

bonus: $(BONUS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone "$(MLX_REPO)" "$(MLX_DIR)"; \
	fi
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(MANDATORY): $(MANDATORY_OBJ) $(LIB)
	$(CC) $(CFLAGS) $^ -lXext -lX11 -lm -lz -o $@

$(BONUS): $(BONUS_OBJ) $(LIB)
	$(CC) $(CFLAGS) $^ -lXext -lX11 -lm -lz -o $@

$(LIBFT_FILE):
	$(MAKE) bonus -C $(LIBFT_DIR)

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
	rm -f $(MANDATORY) $(BONUS)
	rm -rf $(MLX_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(FT_PRINTF_DIR)

re: fclean all

mlx:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone "$(MLX_REPO)" "$(MLX_DIR)"; \
	else \
		echo "MLX exists!!"; \
	fi

compile:
	@echo "[" > compile_commands.json; \
	SEP=""; \
	for SRC in $$(find . -name "*.c"); do \
		echo "$$SEP{" >> compile_commands.json; \
		echo "  \"directory\": \"$$PWD\"," >> compile_commands.json; \
		echo "  \"command\": \"cc -Wall -Wextra -Werror  -Ilibft -Ilibft/ft_printf -Iparser -Iraycast -Igame -Iloop -Iutils -Iminilibx-linux -c $$SRC -o /dev/null\"," >> compile_commands.json; \
		echo "  \"file\": \"$$SRC\"" >> compile_commands.json; \
		echo "}" >> compile_commands.json; \
		SEP=","; \
	done; \
	echo "]" >> compile_commands.json

del_compile:
	rm -f compile_commands.json

.PHONY: clean fclean bonus re mlx compile del_compile
