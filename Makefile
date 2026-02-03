NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra #-Werror
CFLAGS += -Iincludes -I$(LIBFT_DIR)
CFLAGS += -I"$(shell brew --prefix readline)/include"

LDFLAGS = -L"$(shell brew --prefix readline)/lib"
LDLIBS = -lreadline -lhistory -lncurses

LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = src/execution/env_exec.c \
	src/execution/execute_pipeline.c \
	src/execution/execute_single.c \
	src/execution/helpers.c \
	src/execution/main.c \
	src/execution/resolve_path.c \
	src/execution/list_utils.c \
	src/execution/envp.c \
	src/execution/env_to_envp.c \
	src/execution/builtins.c \
	src/execution/execute_builtin.c \
	src/parsing/exit.c \
	src/parsing/lex_line.c \
	src/parsing/parse_cmd.c \
	src/parsing/syntax_checker.c \
	src/parsing/token.c \
	src/parsing/builtin.c \
	src/parsing/cmd_utils.c \
	src/parsing/env_parse.c \
	src/parsing/env_utils.c \
	src/parsing/env.c
	

OBJDIR = obj
OBJS = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re