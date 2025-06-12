CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Isrcs -gdwarf-2

VPATH = srcs/pipex:srcs/pipex_utils:srcs/bonus:includes

UTILS = cmd_get_pathname.c \
		cmd_free_split.c \
		cmd_execute.c \
		error.c \
		token_count.c \
		token_get_buflen.c \
		token_tokenizer.c \
		data_management.c \

PIPEX_INC = pipex.h
PIPEX_SRC = pipex.c $(UTILS)

BONUS_INC = pipex_bonus.h
BONUS_SRC = pipex_bonus.c $(UTILS) \
			here_doc_bonus.c \

PIPEX = pipex
BONUS = pipex_bonus
NAME = $(PIPEX) $(BONUS)

OBJ_DIR = obj
LIBFT = libft.a
LIBFT_DIR = libft
LIBFT_FILE = $(LIBFT_DIR)/$(LIBFT)
CFLAGS += -I $(LIBFT_DIR) -I $(LIBFT_DIR)/get_next_line

FT_PRINTF = libftprintf.a
FT_PRINTF_DIR = libft/ft_printf
FT_PRINTF_FILE = $(FT_PRINTF_DIR)/$(FT_PRINTF)
CFLAGS += -I $(FT_PRINTF_DIR)/includes

LIB = $(LIBFT_FILE) $(FT_PRINTF_FILE)

PIPEX_OBJ = $(addprefix $(OBJ_DIR)/, $(PIPEX_SRC:.c=.o))
BONUS_OBJ = $(addprefix $(OBJ_DIR)/, $(BONUS_SRC:.c=.o))

all: $(PIPEX)

bonus: $(BONUS)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(PIPEX): $(PIPEX_OBJ) $(LIB)
	$(CC) $(CFLAGS) $^ -o $@

$(BONUS): $(BONUS_OBJ) $(LIB)
	$(CC) $(CFLAGS) $^ -o $@

$(LIBFT_FILE):
	$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF_FILE):
	$(MAKE) -C $(FT_PRINTF_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(FT_PRINTF_DIR)

fclean: clean
	rm -f $(PIPEX) $(BONUS)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(FT_PRINTF_DIR)

re: fclean all

.PHONY: all bonus clean fclean re
