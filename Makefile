NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
SOURCE_PATH = src/
INCLUDE_PATH = include/
LIBFT_PATH = libft/
HEADER = $(INCLUDE_PATH)ft_printf.h
LIBFT_NAME = $(LIBFT_PATH)libft.a


SRC = $(SOURCE_PATH)ft_printf.c $(SOURCE_PATH)ft_conversions.c

#SRC_BONUS =  ft_lstnew_bonus.c

OBJ = $(SRC:.c=.o)

#OBJ_BONUS = $(SRC_BONUS:.c=.o)

$(NAME): $(LIBFT_NAME) $(OBJ) $(HEADER)
	ar -rs $(NAME) $(OBJ)

all: $(NAME) $(LIBFT_NAME)

$(LIBFT_NAME):
	cd $(LIBFT_PATH)
	make
	cd ..

#%.o : %.c $(HEADER)
#	$(CC) $(CFLAGS) -c $< -o $@

#bonus: $(OBJ) $(OBJ_BONUS)
#	ar -rs $(NAME) $(OBJ) $(OBJ_BONUS)

clean:
	rm -f $(OBJ)
#$(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test bonus so
