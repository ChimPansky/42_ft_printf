LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
include $(LIBFT_DIR)/colors.mk

NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
SOURCE_DIR = src
INCLUDE = include
IFLAGS = -I $(INCLUDE)
PRIVATE_HEADER = $(SOURCE_DIR)/ft_printf_p.h

SRC_FILES = \
	ft_printf.c \
	parsers.c \
	utils.c \
	write_chars.c \
	write_ints_in_order.c \
	write_ints.c \
	write_ptr.c \
	write_unsigned_base_fd.c

SRC = $(addprefix $(SOURCE_DIR)/,$(SRC_FILES))
OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	cp -f $(LIBFT) $(NAME)
	ar -rcs $(NAME) $(OBJ)
	ranlib $(NAME)

test: $(OBJ) $(LIBFT) test.c
	$(CC) -g $(IFLAGS) test.c $(OBJ) $(LIBFT)  -o test.elf
	./test.elf

# when rebuild libft if no libft obj deps specified?
.PHONY: $(LIBFT)
$(LIBFT): | $(LIBFT_INCL_HEADER)
	make -C $(LIBFT_DIR)
# ln -sf $(LIBFT_DIR)/libft.h $(INCLUDE)/libft.h

%.o : %.c $(PRIVATE_HEADER)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

bonus: $(NAME)

clean:
	make -C $(LIBFT_DIR) fclean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(LIBFT_NAME)

re: fclean all

.PHONY: all clean fclean re test bonus
