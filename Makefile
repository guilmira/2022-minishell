# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/11 07:28:58 by guilmira          #+#    #+#              #
#    Updated: 2021/12/10 11:37:07 by guilmira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--------------------------------------------------------------------------------------------------------------COMPILER
NAME		= minishell
CC			= gcc -g
CFLAGS		= -Wall -Wextra -Werror #-g -fsanitize=address
#--------------------------------------------------------------------------------------------------------------LIBS
LIB_DIR		= libft_submodule
LIB			= $(LIB_DIR)/libft.a
INCLUDES	= -I ./0includes -I ./libft_submodule/0includes
#--------------------------------------------------------------------------------------------------------------SOURCES
SRCS		=	main.c processes.c builtins.c builtins_2.c \
				ft_str_arr_sort.c  builtin_utils.c utilities.c msh_cd_utils.c \
				execution.c 0files.c 0parser.c 0reader.c \
				1mid_parent_son.c 2son.c 4auxiliar.c 5mgmt.c \
				reader_auxiliar.c reader.c
OBJS		=	$(SRCS:.c=.o)
#--------------------------------------------------------------------------------------------------------------RULES

RM = rm -f
VPATH = src include parser process

all: $(LIB) $(NAME)

$(LIB):
	@make -C $(LIB_DIR)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIB) $(INCLUDES_LIBX) -o $(NAME)
	@echo $(GREEN) "$(NAME) compiled" $(NONE)

exe: $(NAME)
	./$(NAME)
#ls -la | wc -l | cat | cat | cat | cat | cat
clean:
	@$(RM) $(OBJS)
	@make clean -C $(LIB_DIR)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIB_DIR)

re: fclean all

norm:
	norminette ./src ./include $(LIB_DIR)

.PHONY: all clean fclean re norm
#--------------------------------------------------------------------------------------------------------------FORMAT
NONE='\033[0m'
GREEN='\033[1;32m'