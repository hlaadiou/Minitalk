# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlaadiou <hlaadiou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/17 16:43:26 by hlaadiou          #+#    #+#              #
#    Updated: 2023/03/17 17:07:53 by hlaadiou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= client.c server.c
OBJS	= $(SRCS:.c=.o)
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra
NAME	= server client