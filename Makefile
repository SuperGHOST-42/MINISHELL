# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/07 18:02:43 by hgutterr          #+#    #+#              #
#    Updated: 2026/01/30 22:38:05 by hgutterr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g
RL_FLAGS = -lreadline -lhistory -lncurses

OBJDIR = obj
SRCDIR = src
SRCS = \
	$(SRCDIR)/main.c \
	$(SRCDIR)/env.c \
	$(SRCDIR)/env_parse.c \
	$(SRCDIR)/env_utils.c \
	$(SRCDIR)/token.c \
	$(SRCDIR)/syntax_checker.c \
	$(SRCDIR)/exit.c \
	$(SRCDIR)/lex_line.c \
	$(SRCDIR)/parse_cmd.c \
	$(SRCDIR)/builtins.c \
	$(SRCDIR)/builtins_impl.c \
	$(SRCDIR)/cmd_utils.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
NAME = minishell

LIBFT_DIR = includes/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

all: $(LIBFT_LIB) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(RL_FLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(LIBFT_INC) -c $< -o $@

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re