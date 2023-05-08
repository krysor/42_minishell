# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 20:29:18 by yaretel-          #+#    #+#              #
#    Updated: 2023/05/08 09:14:57 by yaretel-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT =		dmy
NAME =			$(PROJECT)
HEADER =		includes/$(PROJECT).h
LIB =			lib$(PROJECT).a
SRCS =			dynmem\
				actions_switch\
				lst\
				lst_utils
SRC_MAIN = 		
OBJS =			$(addprefix obj/, $(addsuffix .o, $(SRCS)))
OBJS_MAIN =		$(addprefix obj/, $(addsuffix .o, $(SRC_MAIN)))
CFLAGS =		
FTFLAGS = 		-Wall -Wextra -Werror
FLAGS =			$(CFLAGS) $(FTFLAGS)

all:	$(LIB)

#$(NAME): $(DEPS) $(OBJS) $(OBJS_MAIN)
#	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(OBJS_MAIN) $(DEPS)

obj/%.o: src/%.c $(HEADER)
	mkdir -p $(dir $@)
	$(CC) -c $(FLAGS) -o $@ $<

$(DEPS):
	make -C $(dir $@) FLAGS='$(FLAGS)'

lib: $(LIB)

$(LIB): $(OBJS)
	ar -rcs $(LIB) $(OBJS)

clean:
	rm -rf $(dir $(OBJS))

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIB)

re: fclean all

debug:
	$(MAKE) CFLAGS="-g"

print_obj_names:
				@echo $(OBJS)

.PHONY: re all clean fclean debug lib
