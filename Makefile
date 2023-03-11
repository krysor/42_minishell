# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaretel- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/08 14:17:01 by yaretel-          #+#    #+#              #
#    Updated: 2023/03/09 11:12:19 by yaretel-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT =		minishell
NAME =			$(PROJECT)
HEADER =		includes/$(PROJECT).h
LIB =			lib$(PROJECT).a
SRCS =			lexer\
				utils
SRC_MAIN = 		main
OBJS =			$(addprefix obj/, $(addsuffix .o, $(SRCS)))
OBJS_MAIN =		$(addprefix obj/, $(addsuffix .o, $(SRC_MAIN)))
CFLAGS =		
FTFLAGS = 		-Wall -Wextra -Werror
FLAGS =			$(CFLAGS) $(FTFLAGS)

all: 		$(NAME)

$(NAME): $(DEPS) $(OBJS) $(OBJS_MAIN)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(OBJS_MAIN) $(DEPS)

obj/%.o: src/%.c $(HEADER)
	mkdir -p $(dir $@)
	$(CC) -c $(FLAGS) -o $@ $<

lib: fclean debug $(LIB)

$(LIB): $(DEPS) $(OBJS)
	ar -rcs $(LIB) $(OBJS)

clean:
	rm -rf $(dir $(OBJS))

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIB)

re: fclean all

debug:
	$(MAKE) CFLAGS="-g"

.PHONY: re all clean fclean debug lib
