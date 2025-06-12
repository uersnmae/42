CC = clang
CFLAGS = -Wall -Wextra -Werror -Iincludes -Isrcs -g

VPATH = srcs:srcs/stack:srcs/push_swap:srcs/checker:includes
STACK_INC = stack.h
STACK_SRC = data_management.c \
            op_push.c \
            op_rotate.c \
            op_rotate_reverse.c \
            op_swap.c \
            op_utils.c \
            stack_init.c \
            stack_utils.c \
			free_split.c

PUSH_SWAP_INC = $(STACK_INC) push_swap.h
PUSH_SWAP_SRC = $(STACK_SRC) \
                chunk_sort.c \
                chunk_split.c \
                chunk_utils.c \
                move.c \
                opti_sort_three.c \
                opti_to_top.c \
                sort.c \
                push_swap.c \
				opti_easy_sort.c \

CHECKER_INC = $(STACK_INC) checker_bonus.h
CHECKER_SRC = $(STACK_SRC) \
			  checker_bonus.c \
			  do_operations_bonus.c \
			  checker_gnl_bonus.c \

PUSH_SWAP = push_swap
CHECKER = checker
NAME = $(PUSH_SWAP) $(CHECKER)

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

PUSH_SWAP_OBJ = $(addprefix $(OBJ_DIR)/, $(PUSH_SWAP_SRC:.c=.o))
CHECKER_OBJ = $(addprefix $(OBJ_DIR)/, $(CHECKER_SRC:.c=.o))

all: $(PUSH_SWAP)

bonus: $(CHECKER)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(PUSH_SWAP): $(PUSH_SWAP_OBJ) $(LIB)
	$(CC) $(CFLAGS) $^ -o $@

$(CHECKER): $(CHECKER_OBJ) $(LIB)
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
	rm -f $(PUSH_SWAP) $(CHECKER)
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(FT_PRINTF_DIR)

re: fclean all

.PHONY: all bonus clean fclean re
