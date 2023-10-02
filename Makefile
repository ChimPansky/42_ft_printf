NAME = libftprintf.a
CC = cc
# CFLAGS = -Wall -Werror -Wextra
SOURCE_DIR = src
INCLUDE = include
IFLAGS = -I $(INCLUDE)
HEADER = $(INCLUDE)/ft_printf.h

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_HEADER = $(LIBFT_DIR)/libft.h
LIBFT_INCL_HEADER = $(INCLUDE)/libft.h

#Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SRC_FILES = ft_printf.c # ft_conversions.c puthex_fd.c
SRC = $(addprefix $(SOURCE_DIR)/,$(SRC_FILES))
OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	cp -f $(LIBFT) $(NAME)
	ar -rcs $(NAME) $(OBJ)
	ranlib $(NAME)
# @echo "$(GREEN)Library $(NAME) created!$(DEF_COLOR)"

test: $(NAME) src/test.c
	$(CC) $(CFLAGS) $(IFLAGS) src/test.c $(NAME) -o test.elf
	./test.elf

# when rebuild libft if no libft obj deps specified?
.PHONY: $(LIBFT)
$(LIBFT): | $(LIBFT_INCL_HEADER)
	make -C $(LIBFT_DIR)

$(LIBFT_INCL_HEADER):
	ln -fs $(LIBFT_HEADER) $(LIBFT_INCL_HEADER)

%.o : %.c $(INCLUDE) $(LIBFT_HEADER)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

bonus: $(NAME)

clean:
	make -C $(LIBFT_DIR) fclean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(LIBFT_NAME)

re: fclean all

.PHONY: all clean fclean re test bonus so
