SRC = ./src/main.c \
		./src/memory/memory_tracker.c \
		./src/parser/ft_strnstr.c \
		./src/prompt/get_cli.c \
		./src/prompt/prompt.c \
		./src/prompt/prompt_utiles.c \
		./src/utiles/global_utiles.c

OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
NAME = minishell
INCLUDE = ./src/include/minishell.h

all : $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) -lreadline -lncurses -o $(NAME)

%.o: %.c $(INCLUDE)
	cc $(C_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all