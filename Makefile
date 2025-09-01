# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcausseq <bcausseq@42angouleme.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/17 01:17:51 by bcausseq          #+#    #+#              #
#    Updated: 2025/09/01 21:11:03 by bcausseq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC 			= cc

CFLAGS		= -Wall -Wextra -Werror -g
#CFLAGS		= -Wall -Wextra -Werror=vla -g -O0 -fno-builtin -mno-omit-leaf-frame-pointer -fno-omit-frame-pointer -fsanitize=address,pointer-compare,pointer-subtract,leak,undefined,shift,shift-exponent,shift-base,integer-divide-by-zero,unreachable,vla-bound,null,signed-integer-overflow,bounds,alignment,float-divide-by-zero,float-cast-overflow,nonnull-attribute,returns-nonnull-attribute,bool,enum,pointer-overflow,builtin -fsanitize-address-use-after-scope

NAME		= minishell

LIBFT		= ./libft

LIBFT_LIB	= $(LIBFT)/libft.a

HEADER		= includes

SRCS		= src/main.c\
			  src/prompt_handle.c\
			  src/exec.c\
			  src/exit.c\
			  src/valid_line.c\
			  src/env_manager.c\
			  src/env_utils.c\
			  src/env_secure.c\
			  src/utils_stupid.c\
			  src/path_finder.c\
			  src/env.c\
			  src/cd.c\
			  src/unset.c\
			  src/pwd.c\
			  src/export.c\
			  src/extender.c\
			  src/signals.c\
			  src/lexer_tokens.c\
			  src/lexer_tok.c\
			  src/lexer_utils.c\
			  src/token_handle.c\
			  src/extender.c\
			  src/qotes_remove.c\
			  src/token_up.c\
			  src/extender_utils.c\
			  src/parser_handle.c\
			  src/redir_handle.c\
			  src/echo.c\
			  src/here_doc.c\
			  src/free.c\
			  src/token_utils.c\
			  src/here_doc_signals.c\
			  src/build.c\
			  src/child_signals_and_utils.c\
			  src/child_utils.c\
			  src/exec_func.c\
			  src/builtin_handle.c

OBJ_DIR		= build

OBJ			= $(SRCS:.c=.o)

OBJ			:= $(addprefix $(OBJ_DIR)/manda/,$(OBJ))

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
BOLD = \033[1m
RESET = \033[0m

# Progress bar variables
TOTAL_FILES = $(words $(SRCS))
COMPILED_FILES = 0

define show_header
	@echo "$(RED)$(BOLD)"
	@echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "$(RESET)"
	@echo "$(YELLOW)                    🔥 Rising from the depths of Hell 🔥$(RESET)"
	@echo "$(PURPLE)                         by $(BOLD)bcausseq.... &Co.$(RESET)"
	@echo ""
	@echo "$(CYAN)minihell: $(WHITE)Minishell Improves Nothing, It is a Hell Extention Level, Love it.$(RESET)"
	@echo ""
endef

define progress_bar
	$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES) + 1))))
	@printf "$(GREEN)["; \
	filled=$$(($(COMPILED_FILES) * 50 / $(TOTAL_FILES))); \
	for i in $$(seq 1 $$filled); do printf "█"; done; \
	for i in $$(seq $$(($$filled + 1)) 50); do printf "░"; done; \
	printf "] %d/%d files (%.0f%%)$(RESET)\r" $(COMPILED_FILES) $(TOTAL_FILES) $$(($(COMPILED_FILES) * 100 / $(TOTAL_FILES)))
endef

all:					$(NAME)

$(NAME):				$(OBJ)
	@echo "$(YELLOW)🔗 Linking minishell...$(RESET)"
	@make --no-print-directory -C $(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_LIB) -lreadline
	@echo ""
	$(call show_header)
	@echo "$(GREEN)$(BOLD)✅ MINISHELL COMPILED SUCCESSFULLY! ✅$(RESET)"
	@echo "$(RED)🔥 Welcome to Hell! Your shell awaits... 🔥$(RESET)"
	@echo ""

$(OBJ_DIR)/manda/%.o:	%.c
	@mkdir -p $(@D)
	@printf "$(BLUE)Compiling $(notdir $<)...$(RESET) "
	@$(CC) $(CFLAGS) -I$(LIBFT) -I$(HEADER) -c $< -o $@
	$(call progress_bar)
	@printf "\n"

clean:
	@echo "$(YELLOW)🧹 Cleaning object files...$(RESET)"
	@make --no-print-directory -C $(LIBFT) clean
	@rm -f $(OBJ)
	@echo "$(GREEN)✨ Clean completed!$(RESET)"

fclean:					clean
	@echo "$(YELLOW)🗑️  Full clean in progress...$(RESET)"
	@make --no-print-directory -C $(LIBFT) fclean
	@rm -f $(NAME)
	@echo "$(GREEN)💀 Everything purged from Hell!$(RESET)"

re:						fclean all

credit:
	@printf "$(GREEN)$(BOLD)bcausseq\nrgramati\n$(RESET)"

moral:
	@printf "$(BLUE)lumugot\nfparis\nkzhen-cl\npboucher\nmbirou\n$(RESET)"

destitute:
	@printf "$(RED)ypoulett\nllage\nrvitiell\nLe Staff\nNorminette\n$(RESET)"

.PHONY: all clean fclean re credit destitute
