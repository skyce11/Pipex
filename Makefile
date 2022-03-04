# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: migonzal <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/15 12:09:21 by migonzal          #+#    #+#              #
#    Updated: 2022/03/04 09:44:42 by migonzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = pipex.c ./Libft/ft_split.c ./Libft/ft_strjoin.c ./Libft/ft_strnstr.c ./Libft/ft_putstr_fd.c ./Libft/ft_memmove.c ./Libft/ft_strdup.c ./Libft/ft_strlen.c ./Libft/ft_memcpy.c

OBJS = ${SRCS:.c=.o}

NAME = pipex

cc = gcc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re