# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/11 07:28:58 by guilmira          #+#    #+#              #
#    Updated: 2022/01/17 12:32:16 by guilmira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--------------------------------------------------------------------------------------------------------------COMPILER
NAME		= minishell
CC			= gcc -g
CFLAGS		= -Wall -Wextra -Werror -g -fsanitize=address
READLINE	= -lreadline -lcurses
#sudo apt-get install libreadline-dev 
#--------------------------------------------------------------------------------------------------------------LIBS
LIB_DIR		= libft_submodule
LIB			= $(LIB_DIR)/libft.a
INCLUDES	= -I ./0includes -I ./libft_submodule/0includes
#--------------------------------------------------------------------------------------------------------------SOURCES
SRCS		=	main.c processes.c builtins.c builtins_2.c ft_str_arr_sort.c \
  				builtin_utils.c utilities.c echo.c cd.c export.c unset.c \
  				exit.c ft_strtok.c \
				execution.c 0files.c 0parser.c 0reader.c \
				1mid_parent_son.c 1single_process.c 2son.c 4auxiliar.c 5mgmt.c \
				initialization.c pre_filter.c pre_filter_aux.c \
				reader_auxiliar.c reader.c \
				lexer.c lexer_class.c build_command_table.c quote_mgmt.c quote_split.c \
				printstemp.c \
				signals.c
OBJS		=	$(SRCS:.c=.o)
#--------------------------------------------------------------------------------------------------------------RULES

RM = rm -rf
VPATH = src include parser lexer process

all: $(LIB) $(NAME)

$(LIB):
	@make -C $(LIB_DIR)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(READLINE) $(INCLUDES) $(LIB) -o $(NAME)
	@echo $(GREEN) "$(NAME) compiled" $(NONE)

exe: $(NAME)
	./$(NAME)

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