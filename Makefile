# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/08 14:17:01 by yaretel-          #+#    #+#              #
#    Updated: 2023/05/08 09:21:18 by yaretel-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT =		minishell
NAME =			$(PROJECT)
HEADER =		includes/$(PROJECT).h
LIB =			lib$(PROJECT).a
DEPS_NAME =		ft\
				dmy
DEPS =			$(foreach dep, $(DEPS_NAME), deps/$(dep)/lib$(dep).a)
SRCS =			create_tokcod\
				utils\
				utils2\
				tokcod_to_list\
				create_wrdcod\
				expand_toknode\
				expand_toknode_utils\
				lex_it\
				executor\
				executor_utils\
				parser\
				utils_parser\
				utils_parser_update_cmd\
				utils_free\
				utils_print\
				utils_main\
				rdr\
				get_path\
				builtins\
				builtins_export\
				builtins_unset\
				builtins_echo\
				expander_utils\
				builtins_cd\
				expander
SRC_MAIN = 		main
OBJS =			$(addprefix obj/, $(addsuffix .o, $(SRCS)))
OBJS_MAIN =		$(addprefix obj/, $(addsuffix .o, $(SRC_MAIN)))
OBJS_DEPS :=	$(foreach dep, $(DEPS_NAME), $(addprefix deps/$(dep)/, $(shell $(MAKE) --no-print-directory -C deps/$(dep) print_obj_names)))
CFLAGS =		#-fsanitize=address
FTFLAGS = 		-Wall -Wextra -Werror
FLAGS =			$(CFLAGS) $(FTFLAGS)

all: 		$(NAME)

$(NAME): $(DEPS) $(OBJS) $(OBJS_MAIN)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(OBJS_MAIN) $(DEPS) -lreadline -L/$(HOME)/.brew/opt/readline/lib

obj/%.o: src/%.c $(HEADER)
	mkdir -p $(dir $@)
	$(CC) -c $(FLAGS) -o $@ $<

$(DEPS):
	make -C $(dir $@) FLAGS='$(FLAGS)'

lib: $(LIB)

$(LIB): $(DEPS) $(OBJS)
	ar -rcs $(LIB) $(OBJS) $(OBJS_DEPS)

clean:
	rm -rf $(dir $(OBJS))
	$(foreach dep, $(DEPS_NAME), $(MAKE) $@ -C deps/$(dep);)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIB)
	rm -rf $(DEPS)

re: fclean all

debug:
	$(MAKE) CFLAGS="-g"

.PHONY: re all clean fclean debug lib
