# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asoria <asoria@stedent.42madrid.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/15 00:26:06 by asoria            #+#    #+#              #
#    Updated: 2026/01/06 02:49:09 by asoria           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC		?= cc
CFLAGS		?= -Wall -Wextra -Werror -Wpedantic -g3
CPPFLAGS	?= -Iincludes -Iincludes/libft
SRC_DIR		:= src
OBJ_DIR		:= obj
OBJ		= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
LIBFT_DIR	:= includes/libft
LDLIBS 		= -lreadline
LIBFT		:= $(LIBFT_DIR)/libft.a
TARGET_DIR	:= target
RM		?= rm
BUILTIN_SRC_DIR	:= $(SRC_DIR)/builtin

SRC	:= \
	$(SRC_DIR)/minishell.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/parsing.c \
	$(SRC_DIR)/debug.c \
	$(SRC_DIR)/cleanup.c \
	$(SRC_DIR)/executing.c \
	$(SRC_DIR)/tokens.c \
	$(SRC_DIR)/clusters.c \
	$(SRC_DIR)/pipes.c \
	$(BUILTIN_SRC_DIR)/cd.c \
	$(BUILTIN_SRC_DIR)/pwd.c

all:	$(NAME)

clean:
	$(RM) -f ".msrc"
	$(RM) -f ".ms_history"
	$(RM) -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	$(RM) -rf $(TARGET_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) clean

re:
	$(MAKE) fclean
	$(MAKE) all

$(NAME): $(LIBFT) $(OBJ) | $(TARGET_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDLIBS) -o $(TARGET_DIR)/$(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/builtin

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: all clean fclean re

