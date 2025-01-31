NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror   -g -fsanitize=address
INC = ./include/minishell.h
RM = rm -f

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m


SRCS =	./src/main/main.c \
		./src/components/execution/creat_child.c \
		./src/components/execution/error_handling.c \
		./src/components/execution/execution.c \
		./src/components/execution/find_command_path.c \
		./src/components/execution/pipex.c \
		./src/components/parser/parser.c \
		./src/components/parser/creat_env/creat_env.c \
		./src/components/parser/prompt/get_cli.c \
		./src/components/parser/prompt/get_next_line.c \
		./src/components/parser/prompt/get_next_line_utils.c \
		./src/components/parser/prompt/prompt_utiles.c \
		./src/components/parser/prompt/prompt.c \
		./src/lib/memory/memory_tracker.c \
		./src/lib/ft_atoi.c \
		./src/lib/ft_isdigit.c \
		./src/lib/ft_isspace.c \
		./src/lib/ft_splite.c \
		./src/lib/ft_split_shell.c \
		./src/lib/ft_strcat.c \
		./src/lib/ft_strchr.c \
		./src/lib/ft_strcpy.c \
		./src/lib/ft_strdup.c \
		./src/lib/ft_strjoin.c \
		./src/lib/ft_strlcpy.c \
		./src/lib/ft_strlen.c \
		./src/lib/ft_strncmp.c \
		./src/lib/ft_strstr.c \
		./src/lib/ft_strtok.c \
		./src/lib/ft_strtrim.c \
		./src/lib/ft_substr.c \
		./src/lib/print_err.c \



OBJS = $(SRCS:.c=.o)
OBJSB = $(SRCSB:.c=.o)

all: ${NAME}

${NAME}: ${OBJS}
	@printf "$(GREEN)Building: ${NAME}$(RESET)\n"
	${CC} ${FLAGS} ${OBJS} -o ${NAME}  -lreadline -lncurses

%.o: %.c ${INC}
	@printf "$(YELLOW)Compiling: $<$(RSEST)\n"
	@${CC} ${FLAGS} -c $< -o $@


clean:
	@printf "$(RED)Cleaning object files...$(RESET)\n"
	@$(RM) $(OBJS) $(OBJSB)

fclean: clean
	@printf "$(RED)Removing executable...$(RESET)\n"
	@$(RM) ${NAME}

re: fclean all

.PHONY: all clean fclean re