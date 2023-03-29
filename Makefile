# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/08 14:17:01 by yaretel-          #+#    #+#              #
#    Updated: 2023/03/23 10:58:18 by kkaczoro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT =		minishell
NAME =			$(PROJECT)
HEADER =		includes/$(PROJECT).h
LIB =			lib$(PROJECT).a
DEPS_NAME =		ft
DEPS =			$(foreach dep, $(DEPS_NAME), deps/$(dep)/lib$(dep).a)
SRCS =			create_tokcod\
				utils\
				utils2\
				create_tokenlist\
				create_wrdcod\
				expand_node\
				lex_it\
				parser
SRC_MAIN = 		main
OBJS =			$(addprefix obj/, $(addsuffix .o, $(SRCS)))
OBJS_MAIN =		$(addprefix obj/, $(addsuffix .o, $(SRC_MAIN)))
OBJS_DEPS :=		$(foreach dep, $(DEPS_NAME), $(addprefix deps/$(dep)/, $(shell $(MAKE) --no-print-directory -C deps/$(dep) print_obj_names)))
CFLAGS =		-fsanitize=address
FTFLAGS = 		-Wall -Wextra -Werror
FLAGS =			$(CFLAGS) $(FTFLAGS)

all: 		$(NAME)

$(NAME): $(DEPS) $(OBJS) $(OBJS_MAIN)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(OBJS_MAIN) $(DEPS) -lreadline -L/Users/$(USER)/.brew/opt/readline/lib

obj/%.o: src/%.c $(HEADER)
	mkdir -p $(dir $@)
	$(CC) -c $(FLAGS) -o $@ $<

$(DEPS):
	make -C $(dir $@) FLAGS='$(FLAGS)'

lib: fclean debug $(LIB)

$(LIB): $(DEPS) $(OBJS)
	ar -rcs $(LIB) $(OBJS) $(OBJS_DEPS)

clean:
	rm -rf $(dir $(OBJS))

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIB)
	rm -rf $(DEPS)

re: fclean all

debug:
	$(MAKE) CFLAGS="-g"

.PHONY: re all clean fclean debug lib
