NAME	= minishell
CC		= cc -g
CFLAGS	= -Wall -Wextra -Werror
RM			= rm -rf

SRCS	= src/minishell.c \
			src/list.c \
			src/free1.c src/free2.c \
			src/list_init_env.c \
			src/redirections.c \
			src/redirections1.c \
			src/redirections2_dollar.c src/redirections_helper.c \
			src/list_init_file.c \
			src/1.parsing.c src/1.parsing2.c \
			src/execute1.c src/execute2.c src/execute3_cd.c src/execute4_pwd.c \
			src/execute5_exit.c src/execute6_env_unset.c  src/execute7_export.c \
			src/execute8_echo.c src/execute9_files.c \
			src/signals1.c src/signals2.c \
			src/error.c \
			src/execute_helpers.c \
	

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


