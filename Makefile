NAME	= minishell
CC		= cc -g
#CFLAGS	= -Wall -Wextra -Werror
RM			= rm -rf

SRCS	= src/minishell.c \
			src/list.c \
			src/free.c \
			src/list_init_env.c \
			src/redirections.c \
			src/redirections1.c \
			src/list_init_file.c \
			src/1.parsing.c \
			src/signals.c \
			#src/create_cmd.s



LIBFT		= ./lib
LIBFT_LIB	= $(LIBFT)/libft.a
LIB_FLAGS	= -lreadline

OBJ_F = ./obj/
OBJS = $(SRCS:src/%.c=$(OBJ_F)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_LIB) $(LIB_FLAGS)

$(OBJ_F)%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

libft:
	make -C $(LIBFT)

clean:
	@make clean -C $(LIBFT)
	$(RM) $(OBJ_F)

fclean: clean
	@make fclean -C $(LIBFT)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re


