NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
SOURCE_DIR = src/
INCLUDE_DIR = include/
LIBFT_DIR = libft/
LIBFT_NAME = libft.a
HEADER = $(INCLUDE_DIR)ft_printf.h

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

SRC_FILES = ft_printf.c ft_conversions.c puthex_fd.c

SRC = $(addprefix $(SOURCE_DIR),$(SRC_FILES))

OBJ = $(SRC:.c=.o)

$(NAME): $(LIBFT_DIR)$(LIBFT_NAME) $(OBJ) $(HEADER)
	ar -rs $(NAME) $(OBJ)
	@echo "$(GREEN)Library $(NAME) created!$(DEF_COLOR)"

all: $(NAME)

$(LIBFT_DIR)$(LIBFT_NAME):
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)$(LIBFT_NAME) ./$(NAME)

#mv $(LIBFT_DIR)$(LIBFT_NAME) ./$(NAME)

%.o : %.c $(HEADER)
	$(CC) -I $(INCLUDE_DIR) $(CFLAGS) -g -c $< -o $@

#bonus: $(OBJ) $(OBJ_BONUS)
#	ar -rs $(NAME) $(OBJ) $(OBJ_BONUS)

clean:
	make -C $(LIBFT_DIR) fclean
	rm -f $(OBJ)
#$(OBJ_BONUS)

fclean: clean
	rm -f $(NAME) $(LIBFT_NAME)

re: fclean all

.PHONY: all clean fclean re test bonus so
