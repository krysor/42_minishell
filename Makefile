# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkaczoro <kkaczoro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/08 14:17:01 by yaretel-          #+#    #+#              #
#    Updated: 2023/05/22 20:10:55 by yaretel-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT =		minishell
NAME =			$(PROJECT)
HEADER =		includes/$(PROJECT).h
LIB =			lib$(PROJECT).a
DEPS_NAME =		ft\
				dmy
DEPS =			$(foreach dep, $(DEPS_NAME), deps/$(dep)/lib$(dep).a)
SRCS =			get_line\
				create_tokcod\
				utils\
				utils2\
				utils3\
				tokcod_to_list\
				create_wrdcod\
				expand_toknode\
				expand_toknode_utils\
				lex_it\
				executor\
				handle_redirections\
				executor_utils\
				parser\
				parser_utils\
				parser_utils_2\
				utils_free\
				utils_print\
				rdr\
				get_path\
				builtins\
				builtins_export_utils\
				builtins_export_noargs\
				builtins_unset\
				builtins_echo\
				expander_utils\
				builtins_cd\
				builtins_exit\
				builtins_utils\
				expander\
				main_utils\
				get_next_line\
				signals
SRC_MAIN = 		main
OBJS =			$(addprefix obj/, $(addsuffix .o, $(SRCS)))
OBJS_MAIN =		$(addprefix obj/, $(addsuffix .o, $(SRC_MAIN)))
OBJS_DEPS :=	$(foreach dep, $(DEPS_NAME), $(addprefix deps/$(dep)/, $(shell $(MAKE) --no-print-directory -C deps/$(dep) print_obj_names)))
CFLAGS =		
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
