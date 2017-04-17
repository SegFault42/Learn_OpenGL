# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rabougue <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/10 19:16:51 by rabougue          #+#    #+#              #
#    Updated: 2017/04/10 03:47:29 by rabougue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####################################_COLOR_#####################################
GREEN = \033[38;5;10m
GREY = \033[38;5;60m
RED = \033[38;5;9m
END = \033[0m
##################################_COMPILATION_#################################
NAME = openGL
CC = gcc
#FLAG = -Weverything
#FLAG = -Wall -Wextra -Werror

SRCS =	./source/main.c\

OBJS = $(SRCS:.c=.o)

##################################_OPENGL_SDL#_#################################
LINKER = -lGLEW -lSDL2 -framework OpenGL
INCLUDE = -L./SDL2-2.0.5/include/
PKG_CONFIG = `sdl2-config --cflags --libs`
################################################################################

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(SRCS) $(LINKER) $(PKG_CONFIG) -o $(NAME) $(OBJS) $(INCLUDE)
	@printf "✅  Compilation done.\n"

%.o : %.c
	@printf " ✅                                                              \r"
	@printf "✅  $(notdir $<)\r"
	$(CC) $(SRCS) $(LINKER) $(PKG_CONFIG) -o $(NAME) $(OBJS) $(INCLUDE)

clean:
	@printf "                                                               \r"
	@printf "✅  all .o deleted\n"
	@rm -f $(OBJS)
	@make -s clean -C ./libft/

fclean:
	@printf "                                                               \r"
	@printf "✅  libft.a, all .o and minishell deleted\n"
	@rm -f $(NAME) $(OBJS)
	@make -s fclean -C ./libft/

re: fclean all
