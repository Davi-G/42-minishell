#------------MakeFile------------#
NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

FILES = ft_printf \
		ft_printf_utils \
		ft_printf_types \
		ft_printf_types_1 \

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $^

$(NAME): $(OBJS)
	$(AR) $@ $^

test: $(NAME) main_printf.c
	$(CC) $(CFLAGS) main_printf.c $(NAME) -o test

all: $(NAME)

so:
	$(CC) $(CFLAGS) -o so $(OBJS) -shared

clean:
	$(RM) $(OBJS) $(OBJS_B) so test

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re so