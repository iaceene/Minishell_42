NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror  -g3 -fsanitize=address
INC = ./include/minishell.h
INCE = ./include/execution.h
INCP = ./include/parser.h
ALL_INCS = $(INC) $(INCP) $(INCE)
RM = rm -f

SRCS =	./src/main/main.c \
		./src/components/execution/builtin/builtin_cd_help.c \
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
		./src/components/execution/execute/find_command_path_utils1.c \
		./src/components/execution/execute/find_command_path.c \
		./src/components/execution/execute/pipex_utilse1.c \
		./src/components/execution/execute/pipex_utilse2.c \
		./src/components/execution/execute/pipex.c \
		./src/components/parser/init/parser_utiles.c \
		./src/components/parser/init/parser.c \
		./src/components/parser/init/parser_utiles_one.c \
		./src/components/parser/init/redir_handler.c \
		./src/components/parser/init/split_adv.c \
		./src/components/parser/expander/expander.c \
		./src/components/parser/expander/expander_utiles_two.c \
		./src/components/parser/expander/expander_utiles_tree.c \
		./src/components/parser/expander/handlers.c \
		./src/components/parser/herdoc/herdoc_utile_one.c \
		./src/components/parser/herdoc/heredoc_prc.c \
		./src/components/parser/herdoc/herdoc.c \
		./src/components/parser/expander/heredoc_expander.c \
		./src/components/parser/expander/hard_code_pids.c \
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
		./src/lib/ft_putstr_fd.c \
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
		./src/lib/ft_strcmp.c \
		./src/lib/ft_strstr.c \
		./src/lib/ft_strtok.c \
		./src/lib/ft_strtrim.c \
		./src/lib/ft_substr.c \
		./src/lib/linked_list.c \
		./src/lib/print_err.c \
		./src/lib/ft_same.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -lreadline -lncurses

%.o: %.c $(ALL_INCS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
