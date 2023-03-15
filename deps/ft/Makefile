# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaretel- <yaretel-@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/13 16:40:42 by yaretel-          #+#    #+#              #
#    Updated: 2023/03/15 09:06:37 by yaretel-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER		=	libft.h
SRCS		=	ft_atoi.c\
				ft_bzero.c\
				ft_calloc.c\
				ft_isalnum.c\
				ft_isalpha.c\
				ft_isascii.c\
				ft_isdigit.c\
				ft_isprint.c\
				ft_itoa.c\
				ft_memchr.c\
				ft_memcmp.c\
				ft_memcpy.c\
				ft_memmove.c\
				ft_memset.c\
				ft_putchar_fd.c\
				ft_putendl_fd.c\
				ft_putnbr_fd.c\
				ft_putstr_fd.c\
				ft_split.c\
				ft_strchr.c\
				ft_strdup.c\
				ft_strjoin.c\
				ft_strlcat.c\
				ft_strlcpy.c\
				ft_strlen.c\
				ft_strmapi.c\
				ft_strncmp.c\
				ft_strnstr.c\
				ft_strrchr.c\
				ft_strtrim.c\
				ft_substr.c\
				ft_tolower.c\
				ft_toupper.c\
				ft_striteri.c\
				ft_base_is_valid.c\
				ft_charstr.c\
				ft_putchar.c\
				ft_putint_base.c\
				ft_putuint_base.c\
				ft_putstr.c\
				ft_putul_base.c\
				ft_setzero.c\
				ft_printf.c

BSRCS		=	ft_lstnew_bonus.c\
				ft_lstadd_front_bonus.c\
				ft_lstsize_bonus.c\
				ft_lstlast_bonus.c\
				ft_lstadd_back_bonus.c\
				ft_lstdelone_bonus.c\
				ft_lstclear_bonus.c\
				ft_lstiter_bonus.c\
				ft_lstmap_bonus.c

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -I.
EXTRAFLAGS	=	
NAME		=	libft.a

ifdef WITH_BONUS
OBJS		= 	$(SRCS:.c=.o) $(BSRCS:.c=.o)
else
OBJS		=	$(SRCS:.c=.o)
endif

all:			$(NAME)

$(NAME):		$(OBJS)
				ar -rcs $(NAME) $(OBJS)

%.o:			%.c $(HEADER)
				$(CC) -c $(CFLAGS) $(EXTRAFLAGS) -o $@ $<

clean:
				rm -f $(OBJS) $(BSRCS:.c=.o)

fclean:			clean
				rm -f $(NAME)

bonus:
				$(MAKE) WITH_BONUS=1 all

re:				fclean all

print_obj_names:
				@echo $(OBJS)

.PHONY:			all bonus clean fclean re test print_obj_names
