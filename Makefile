# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgutterr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/16 15:51:41 by hgutterr          #+#    #+#              #
#    Updated: 2025/12/16 23:40:12 by hgutterr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g
RL_FLAGS = -lreadline -lhistory -lncurses

OBJDIR = obj
SRCDIR = src
SRCS = \
	$(SRCDIR)/main.c \
	$(SRCDIR)/token.c

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
