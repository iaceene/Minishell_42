NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror  -fsanitize=address
INC = ./include/minishell.h
INCE = ./include/execution.h
INCP = ./include/parser.h
RM = rm -f
MKDIR = mkdir -p

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[31m
RESET = \033[0m


SRCS =	./src/main/main.c \
		./src/components/execution/builtin/builtin_cd.c \
		./src/components/execution/builtin/builtin_echo.c \
		./src/components/execution/builtin/builtin_env.c \
		./src/components/execution/builtin/builtin_exit.c \
		./src/components/execution/builtin/builtin_export_help.c \
		./src/components/execution/builtin/builtin_export_help2.c \
		./src/components/execution/builtin/builtin_export.c \
		./src/components/execution/builtin/builtin_pwd.c \
		./src/components/execution/builtin/builtin_unset.c \
		./src/components/execution/builtin/builtin.c \
		./src/components/execution/env/env_create.c \
		./src/components/execution/env/env_utils.c \
		./src/components/execution/env/env_utils1.c \
		./src/components/execution/env/env_utils2.c \
		./src/components/execution/execute/error_handling.c \
		./src/components/execution/execute/execution_cmd.c \
		./src/components/execution/execute/handel_file_redirection.c \
		./src/components/execution/execute/execution.c \
		./src/components/execution/execute/find_command_path.c \
		./src/components/execution/execute/pipex_utilse1.c \
		./src/components/execution/execute/pipex.c \
		./src/components/parser/parser.c \
		./src/components/parser/expander/expander.c \
		./src/components/parser/expander/expander_utiles.c \
		./src/components/parser/expander/expander_utiles_two.c \
		./src/components/parser/expander/handlers.c \
		./src/components/parser/herdoc/herdoc.c \
		./src/components/parser/lexer/final_step.c \
		./src/components/parser/lexer/lexer_utiles.c \
		./src/components/parser/lexer/syntax_checker.c \
		./src/components/parser/lexer/syntax_utiles.c \
		./src/components/parser/lexer/syntax_utiles_two.c \
		./src/components/parser/lexer/lexer.c \
		./src/components/parser/prompt/get_cli.c \
		./src/components/parser/prompt/prompt_utiles.c \
		./src/components/parser/prompt/prompt.c \
		./src/lib/memory/memory_tracker.c \
		./src/lib/ft_atoi.c \
		./src/lib/ft_itoa.c \
		./src/lib/ft_isdigit.c \
		./src/lib/ft_isspace.c \
		./src/lib/ft_memcpy.c \
		./src/lib/ft_memmove.c \
		./src/lib/ft_splite.c \
		./src/lib/ft_strcat.c \
		./src/lib/ft_strchr.c \
		./src/lib/ft_strcpy.c \
		./src/lib/ft_strdup.c \
		./src/lib/ft_strjoin.c \
		./src/lib/ft_strlcat.c \
		./src/lib/ft_strlcpy.c \
		./src/lib/ft_strlen.c \
		./src/lib/ft_strncpy.c \
		./src/lib/ft_strncmp.c \
		./src/lib/ft_strstr.c \
		./src/lib/ft_strtok.c \
		./src/lib/ft_strtrim.c \
		./src/lib/ft_substr.c \
		./src/lib/linked_list.c \
		./src/lib/print_err.c \



OBJS = $(patsubst ./src/%.c, ./obj/%.o, $(SRCS))

OBJ_DIR = ./obj

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${FLAGS} ${OBJS} -o ${NAME} -lreadline -lncurses
	@echo "${GREEN}${NAME} compiled successfully!${RESET}"

$(OBJ_DIR)/%.o: ./src/%.c ${INC} ${INCE} ${INCP}
	@$(MKDIR) $(dir $@)
	@${CC} ${FLAGS} -c $< -o $@
	@echo "${YELLOW}Compiled $< -> $@${RESET}"

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "${RED}Object files removed!${RESET}"

fclean: clean
	@$(RM) ${NAME}
	@echo "${RED}${NAME} removed!${RESET}"

re: fclean all

.PHONY: all clean fclean re


print_error:
	@echo "$(RED)"
	@echo " ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    "
	@echo "▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    "
	@echo "▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    "
	@echo "▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    "
	@echo "▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒"
	@echo "░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░"
	@echo "░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░"
	@echo "░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   "
	@echo "       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░"
	@echo " ⢸⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⡷⠀⠀						"
	@echo " ⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠢⣀⠀⠀					    "
	@echo " ⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇ Are you winning son?	"
	@echo " ⢸⠀⠀⠀⠀ ⠖⠒⠒⠒⢤⠀⠀⠀⠀⠀⡇⠀						"
	@echo " ⢸⠀⠀⣀⢤⣼⣀⡠⠤⠤⠼⠤⡄⠀⠀⡇⠀						"
	@echo " ⢸⠀⠀⠑⡤⠤⡒⠒⠒⡊⠙⡏⠀⢀⠀⡇⠀						"
	@echo " ⢸⠀⠀⠀⠇⠀⣀⣀⣀⣀⢀⠧⠟⠁⠀⡇						"
	@echo " ⢸⠀⠀⠀⠸⣀⠀⠀⠈⢉⠟⠓⠀⠀⠀⠀						"
	@echo " ⢸⠀⠀⠀⠀⠈⢱⡖⠋⠁⠀⠀⠀⠀⠀⠀⡇						"
	@echo " ⢸⠀⠀⠀⠀⣠⢺⠧⢄⣀⠀⠀⣀⣀⠀⠀⡇						"
	@echo " ⢸⠀⠀⠀⣠⠃⢸⠀⠀⠈⠉⡽⠿⠯⡆							"
	@echo " ⢸⠀⠀⣰⠁⠀⢸⠀⠀⠀⠀⠉⠉⠉⠀⠀⡇						"
	@echo " ⢸⠀⠀⠣⠀⠀⢸⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇						"
	@echo " ⢸⠀⠀⠀⠀⠀⢸⠀⢇⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀						"
	@echo "\033[38;2;89;180;195m"
	@echo "                       by: kaneki, iaceene                       "
	@echo "\033[0m"                                                         

.PHONY: all clean fclean re