NAME = minishell

CC = clang
CFLAGS = -Wall -Wextra -Werror -I.

RM = rm -rf

TOKENIZATION_DIR = ./tokenization/
CREATION_AST_DIR = ./creation_ast/
BUTCHER_DIR = ./butcher/
BUILT_IN_DIR = ./built_in/

TOKENIZATION = $(addprefix $(TOKENIZATION_DIR), \
	  tokenization.c free_tokens.c ft_identify_token_type.c\
	  ft_identify_redirections.c token_lists.c ft_quoter.c ft_append_quote.c)

CREATION_AST = $(addprefix $(CREATION_AST_DIR), \
	  ft_checker_is.c ft_create_ast.c ft_create_lists.c\
	  ft_free_stuff.c ft_get_something.c utilities.c)

BUTCHER = $(addprefix $(BUTCHER_DIR), \
	  execute_command.c setup_files.c\
	  start_execution.c help_set_files.c)

BUILT_IN = $(addprefix $(BUILT_IN_DIR), ft_execute_builtin.c\
	  ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c utils_built_ins.c ft_expr.c\
	  ft_echo_utils.c)

SRC = main.c ft_printout.c ft_duplicate_envp.c $(TOKENIZATION) $(CREATION_AST) $(BUTCHER) $(BUILT_IN)

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

.PHONY: all bonus clean fclean re

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C libft

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -lreadline -Llibft -lft -o $(NAME)

%.o: %.c $(LIBFT)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@make clean -C libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft

re: fclean all