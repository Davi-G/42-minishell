#------------MakeFile------------#
NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ./includes/
LDFLAGS = -L /opt/homebrew/Cellar/readline/8.2.7/lib -lreadline

SRCS_DIR = ./src/
SRCS = main.c

OBJS_DIR = ./obj/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

DEPS = $(OBJS:.o=.d)

all: obj $(NAME)

obj:
	mkdir -p obj

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) -o $@ -c $< -g

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) -g

clean:
	rm -rf $(OBJS) $(DEPS)

fclean: clean
	rm -rf $(NAME) $(OBJS_DIR)

re: fclean all

.PHONY: all clean fclean re
#NAME = minishell
#
#CC = gcc
#CFLAGS = -Wall -Wextra -Werror
#
#SRCS_DIR = ./src/
#SRCS =	main.c \
#
#OBJS_DIR = ./obj/
#OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
#
#all: obj $(NAME)
#
#obj:
#	mkdir obj
#
#$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
#	$(CC) $(CFLAGS) -lreadline -I ./includes/ -o $@ -c $< -g
#
#$(NAME): $(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -g
#
#clean:
#	rm -rf $(NAME)
#
#fclean: clean
#	rm -rf obj
#
#re: fclean all
#
#.PHONY: all clean fclean re