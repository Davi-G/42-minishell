#------------MakeFile------------#
NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ./includes/ -I ./42-libft/
LDFLAGS = -L /opt/homebrew/Cellar/readline/8.2.7/lib -lreadline -L ./42-libft -l ft

SRCS_DIR = ./src/
SRCS = main.c \
		parser.c \
		utils.c \
		command_finder.c \
		existing_cmd.c \
		execute_cmd.c \

OBJS_DIR = ./obj/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

DEPS = $(OBJS:.o=.d)

all: lib obj $(NAME)

obj:
	@mkdir -p obj

lib:
	@make -C 42-libft/

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(CC) $(CFLAGS) -o $@ -c $< -g

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) -g

clean:
	@rm -rf $(OBJS) $(DEPS)
	@make fclean -C 42-libft/

fclean: clean
	@rm -rf $(NAME) $(OBJS_DIR)

re: fclean all

.PHONY: all clean fclean re
