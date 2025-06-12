CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g

VPATH = srcs:

PHILO_INC = philo_bonus.h philo_bonus_type.h
PHILO_SRC = philo_bonus.c \
			error.c \
			monitor_thread.c \
			monitor_main.c \
			init_info.c \
			parse_utils.c \
			philo_bonus.c \
			philo_print_state.c \
			philo_routine.c \
			utils.c \

PHILO = philo_bonus
NAME = $(PHILO)

OBJ_DIR = obj

PHILO_OBJ = $(addprefix $(OBJ_DIR)/, $(PHILO_SRC:.c=.o))

all: $(PHILO)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(PHILO): $(PHILO_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(PHILO)

re: fclean all

compile:
	@echo "[" > compile_commands.json; \
	SEP=""; \
	for SRC in $$(find srcs -name "*.c"); do \
		echo "$$SEP{" >> compile_commands.json; \
		echo "  \"directory\": \"$$PWD\"," >> compile_commands.json; \
		echo "  \"command\": \"cc -Wall -Wextra -Werror -Isrcs -Iincludes  -c $$SRC -o /dev/null\"," >> compile_commands.json; \
		echo "  \"file\": \"$$SRC\"" >> compile_commands.json; \
		echo "}" >> compile_commands.json; \
		SEP=","; \
	done; \
	echo "]" >> compile_commands.json

del_compile:
	rm -f compile_commands.json

.PHONY: all clean fclean re compile del_compile
