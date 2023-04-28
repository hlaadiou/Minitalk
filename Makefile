# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/17 16:43:26 by hlaadiou          #+#    #+#              #
#    Updated: 2023/04/28 10:55:51 by hlaadiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_SERVER				= server.c libft_utils.c
SRCS_CLIENT				= client.c libft_utils.c
SRCS_BONUS_SERVER		= server_bonus.c libft_utils_bonus.c
SRCS_BONUS_CLIENT		= client_bonus.c libft_utils_bonus.c
OBJS_SERVER				= $(SRCS_SERVER:.c=.o)
OBJS_CLIENT				= $(SRCS_CLIENT:.c=.o)
OBJS_BONUS_SERVER		= $(SRCS_BONUS_SERVER:.c=.o)
OBJS_BONUS_CLIENT		= $(SRCS_BONUS_CLIENT:.c=.o)
CC						= cc
RM						= rm -f
CFLAGS					= -Wall -Werror -Wextra
NAME					= server
CLIENT_NAME				= client
BONUS_NAME				= server_bonus
BONUS_CLIENT_NAME		= client_bonus

all:					$(NAME) $(CLIENT_NAME)

$(NAME):				$(OBJS_SERVER)
						$(CC) $(CFLAGS) -o $(NAME) $(OBJS_SERVER)

$(CLIENT_NAME):			$(OBJS_CLIENT)
						$(CC) $(CFLAGS) -o $(CLIENT_NAME) $(OBJS_CLIENT)

bonus:					$(BONUS_NAME) $(BONUS_CLIENT_NAME)

$(BONUS_NAME):			$(OBJS_BONUS_SERVER)
						$(CC) $(CFLAGS) -o $(BONUS_NAME) $(OBJS_BONUS_SERVER)

$(BONUS_CLIENT_NAME):	$(OBJS_BONUS_CLIENT)
						$(CC) $(CFLAGS) -o $(BONUS_CLIENT_NAME) $(OBJS_BONUS_CLIENT)

clean:
						$(RM) $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_BONUS_SERVER) $(OBJS_BONUS_CLIENT)

fclean:					clean
						$(RM) $(NAME) $(CLIENT_NAME) $(BONUS_NAME) $(BONUS_CLIENT_NAME)

re:						fclean all

.PHONY:					all clean fclean re