SRC =	./src/main/main.c \
		./src/memory/memory_tracker.c \
		./src/prompt/get_cli.c \
		./src/prompt/prompt.c \
		./src/prompt/prompt_utiles.c \
		./src/utiles/global_utiles.c \
		./src/parser/check_path.c \
		./src/utiles/ft_strjoin.c \
		./src/utiles/print_err.c \
		./src/prompt/get_next_line.c \
		./src/prompt/get_next_line_utils.c \
		./src/utiles/ft_strtrim.c \
		./src/utiles/ft_splite.c \
		./src/parser/env_creator.c

OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
INCLUDE = ./src/include/minishell.h
# DEBUG = -g -fsanitize=address

all : $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) $(DEBUG) -o $(NAME)

%.o: %.c $(INCLUDE)
	cc $(C_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all