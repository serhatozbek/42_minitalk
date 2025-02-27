# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sozbek <sozbek@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/21 00:54:57 by sozbek            #+#    #+#              #
#    Updated: 2025/02/21 01:35:28 by sozbek           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_C = client
NAME_S = server
NAME_CB = client_bonus
NAME_SB = server_bonus
FLAGS = -Wall -Wextra -Werror
FILE1 = client.c
FILE2 = server.c
FILE1B = client_bonus.c
FILE2B = server_bonus.c
CC = cc

all: $(NAME_C) $(NAME_S)

$(NAME_C): $(FILE1)
	$(CC) $(FLAGS) $(FILE1) -o $(NAME_C)

$(NAME_S): $(FILE2)
	$(CC) $(FLAGS) $(FILE2) -o $(NAME_S)

bonus: $(NAME_CB) $(NAME_SB)

$(NAME_CB): $(FILE1B)
	$(CC) $(FLAGS) $(FILE1B) -o $(NAME_CB)

$(NAME_SB): $(FILE2B)
	$(CC) $(FLAGS) $(FILE2B) -o $(NAME_SB)

clean:
	rm -f server
	rm -f client

clean_bonus:
	rm -f server_bonus
	rm -f client_bonus

fclean: clean clean_bonus

re: clean all

re_bonus: clean_bonus bonus 

.PHONY: all clean clean_bonus fclean re bonus rebonus