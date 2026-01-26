# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asoria <asoria@stedent.42madrid.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/15 00:26:06 by asoria            #+#    #+#              #
#    Updated: 2026/01/20 05:39:00 by asoria           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			?= cc
CFLAGS		?= -Wall -Wextra -Werror -Wpedantic -g3
CPPFLAGS	?= -Iincludes -Iincludes/libft
SRC_DIR		:= src
OBJ_DIR		:= obj
OBJ			= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
LIBFT_DIR	:= includes/libft
LDLIBS 		:= -lreadline
LIBFT		:= $(LIBFT_DIR)/libft.a
TARGET_DIR	:= target
RM			?= rm
EXECUTION_SRC_DIR := $(SRC_DIR)/execution
TOKEN_SRC_DIR := $(SRC_DIR)/tokens
PARSE_SRC_DIR := $(SRC_DIR)/parser
BUILTIN_SRC_DIR	:= $(SRC_DIR)/builtin

SRC	:= \
	$(SRC_DIR)/minishell.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/parsing.c \
	$(SRC_DIR)/cleanup.c \
	$(SRC_DIR)/cleanup2.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/utils2.c \
	$(SRC_DIR)/clusters.c \
	$(SRC_DIR)/parameter-expansion.c \
	$(PARSE_SRC_DIR)/parser.c \
	$(PARSE_SRC_DIR)/parser_utils.c \
	$(EXECUTION_SRC_DIR)/executor.c \
	$(EXECUTION_SRC_DIR)/pipes.c \
	$(EXECUTION_SRC_DIR)/executor_utils.c \
	$(EXECUTION_SRC_DIR)/builtins.c \
	$(TOKEN_SRC_DIR)/tokens.c \
	$(TOKEN_SRC_DIR)/tokens_utils.c \
	$(BUILTIN_SRC_DIR)/cd.c \
	$(BUILTIN_SRC_DIR)/env.c \
	$(BUILTIN_SRC_DIR)/echo.c \
	$(BUILTIN_SRC_DIR)/export.c \
	$(BUILTIN_SRC_DIR)/unset.c \
	$(BUILTIN_SRC_DIR)/exit.c \
	$(BUILTIN_SRC_DIR)/pwd.c

all: $(NAME)

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
	mkdir -p $(OBJ_DIR)/$(BUILTIN_SRC_DIR)
	mkdir -p $(OBJ_DIR)/$(TOKEN_SRC_DIR)
	mkdir -p $(OBJ_DIR)/$(EXECUTION_SRC_DIR)

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

.PHONY: all clean fclean re

