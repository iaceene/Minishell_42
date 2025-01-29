SRC = ./src/main.c ./src/parser/ft_strnsstr.c
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