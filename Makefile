NAME            := minishell
CC              ?= cc
CFLAGS          ?= -Wall -Wextra -Werror -Wpedantic -g3
CPPFLAGS        ?= -I. -Iincludes -Iincludes/libft -Isrc
OBJ_DIR         := obj
OBJ             = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
LIBFT_DIR       := includes/libft
LDLIBS          := -lreadline
LIBFT           := $(LIBFT_DIR)/libft.a
TARGET_DIR      := target
RM              ?= rm

SRC_DIR         := src
CORE_DIR        := $(SRC_DIR)/core
GRAMMAR_DIR     := $(SRC_DIR)/grammar
EXECUTION_DIR   := $(SRC_DIR)/execution
BUILTIN_DIR     := $(SRC_DIR)/builtin
UTILS_DIR       := $(SRC_DIR)/utils

SRC_CORE        := minishell.c init.c signals.c

SRC_GRAMMAR     := parsing.c parser.c parser_utils.c \
                   parameter-expansion.c tokens.c \
                   tokens_utils.c tokens_utils_2.c \
		   dollar.c quotes.c

SRC_EXECUTION   := execute_pipes.c executor.c pipes.c executor_utils.c \
			redirections.c heredocs.c

SRC_BUILTIN     := builtins.c redir_builtins.c cd.c echo.c env.c exit.c \
			export.c pwd.c unset.c

SRC_UTILS       := cleanup.c cleanup2.c utils.c utils2.c #debug.c

SRC             := $(addprefix $(CORE_DIR)/, $(SRC_CORE)) \
                   $(addprefix $(GRAMMAR_DIR)/, $(SRC_GRAMMAR)) \
                   $(addprefix $(EXECUTION_DIR)/, $(SRC_EXECUTION)) \
                   $(addprefix $(BUILTIN_DIR)/, $(SRC_BUILTIN)) \
                   $(addprefix $(UTILS_DIR)/, $(SRC_UTILS))

all: $(TARGET_DIR)/$(NAME)

$(TARGET_DIR)/$(NAME): $(LIBFT) $(OBJ) | $(TARGET_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LDLIBS) -o $(TARGET_DIR)/$(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

$(OBJ_DIR)/core/%.o: $(CORE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/grammar/%.o: $(GRAMMAR_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/execution/%.o: $(EXECUTION_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/builtin/%.o: $(BUILTIN_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/utils/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

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

test: re
	valgrind --suppressions=valgrind.supp --track-fds=yes \
	--show-leak-kinds=all --leak-check=full --trace-children=yes ./target/minishell

.PHONY: all clean fclean re test
