# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/11 07:28:58 by guilmira          #+#    #+#              #
#    Updated: 2021/11/17 08:58:58 by guilmira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--------------------------------------------------------------------------------------------------------------COMPILER
NAME		= minishell
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror #-g -fsanitize=address
#--------------------------------------------------------------------------------------------------------------LIBS
LIB_DIR		= libft_submodule
LIB			= $(LIB_DIR)/libft.a
INCLUDES	= -I ./0includes -I ./libft_submodule/0includes
#--------------------------------------------------------------------------------------------------------------SOURCES
SRCS		=	minishell.c
OBJS		=	$(SRCS:.c=.o)
#--------------------------------------------------------------------------------------------------------------RULES
all: $(LIB) $(NAME)

$(LIB):
	@make -C $(LIB_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -Imlx -c $< -o $@

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIB) $(INCLUDES_LIBX) -o $(NAME)
	@echo $(GREEN) "$(NAME) compiled" $(NONE)

exe: $(NAME)
	./$(NAME)

norm:
	norminette $(SRCS)

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIB_DIR)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIB_DIR)

re: fclean all

.PHONY: all clean fclean re
#--------------------------------------------------------------------------------------------------------------FORMAT
NONE='\033[0m'
GREEN='\033[1;32m'