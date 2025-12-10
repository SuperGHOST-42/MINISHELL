CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = libft.a
SRCS = ft_isalpha.c ft_memchr.c ft_putendl_fd.c ft_striteri.c ft_strtrim.c \
	ft_atoi.c ft_isascii.c ft_memcmp.c ft_putnbr_fd.c ft_strlcpy.c ft_substr.c \
	ft_isdigit.c ft_memcpy.c ft_putstr_fd.c ft_strlen.c ft_tolower.c ft_isprint.c \
	ft_memmove.c ft_split.c ft_strmapi.c ft_toupper.c ft_bzero.c ft_itoa.c \
	ft_strncmp.c ft_calloc.c ft_memset.c ft_strchr.c ft_strnstr.c ft_isalnum.c \
	ft_putchar_fd.c ft_strdup.c ft_strrchr.c ft_strlcat.c ft_strjoin.c
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@echo "fclean done."

re: fclean all

