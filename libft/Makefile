# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcausseq <bcausseq@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 22:18:57 by bcausseq          #+#    #+#              #
#    Updated: 2025/08/23 21:58:28 by bcausseq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -g

INCLUDE		= includes

NAME		= libft.a

BUILD_DIR	= build

SRCS_DIRS	= char conversion io memory miscs string

SRCS		= ft_strlen.c\
			  ft_strjoin.c\
			  ft_calloc.c\
			  ft_strcat.c\
			  ft_strncmp.c\
			  ft_bzero.c\
			  ft_strdup.c\
			  ft_strcpy.c\
			  ft_split.c\
			  ft_substr.c\
			  ft_strlcpy.c\
			  get_next_line.c\
			  ft_random_name.c\
			  ft_strchr.c\
			  ft_strcmp.c\
			  ft_strrchr.c\
			  ft_count_word.c\
			  ft_strndup.c\
			  ft_strncpy.c\
			  ft_itoa.c\
			  ft_isupper.c\
			  ft_islower.c\
			  ft_isdigit.c\
			  ft_isspace.c\
			  ft_isalnum.c\
			  ft_isalpha.c\
			  ft_atoll.c\
			  ft_putchar_fd.c\
			  ft_putstr_fd.c\
			  ft_putnbr_fd.c\
			  ft_fprintf.c\
			  ft_fprintf_conv.c\
			  ft_fprintf_spe_cases_sup.c\
			  ft_putnbr_add_fd.c\
			  ft_isdigit_while.c

FULL_SRCS	= $(foreach src,$(SRCS), $(firstword $(foreach dir,$(SRCS_DIRS),$(wildcard $(dir)/$(src)))))

OBJS		= $(patsubst %.c,$(BUILD_DIR)/%.o,$(FULL_SRCS))

# ✨ Magical Colors & Styles ✨
AURORA_PINK = \033[38;5;213m
AURORA_PURPLE = \033[38;5;141m
AURORA_BLUE = \033[38;5;75m
AURORA_GREEN = \033[38;5;121m
AURORA_YELLOW = \033[38;5;228m
DREAMY_CYAN = \033[38;5;159m
COSMIC_GOLD = \033[38;5;220m
STARLIGHT = \033[38;5;231m
MOONBEAM = \033[38;5;189m
RESET = \033[0m
BOLD = \033[1m
DIM = \033[2m

# Dream Animation Frames
define dream_sequence
	@printf "$(AURORA_PINK)$(BOLD)"
	@echo "    ✦ ･ ｡  ✦   ･ ｡ ﾟ☆  ﾟ｡ ✦"
	@echo "  ｡ ﾟ ☆ ｡  ✦ ･ ｡ ✦   ･ ｡ ﾟ☆ "
	@sleep 0.3
	@printf "$(AURORA_PURPLE)"
	@echo "       ･ ｡ ﾟ☆    ✦ ･ ｡"
	@echo "   ✦   ･ ｡ ﾟ☆  ﾟ｡ ✦ ･"
	@sleep 0.3
	@printf "$(AURORA_BLUE)"
	@echo "    ☆  ﾟ｡ ✦ ･ ｡ ✦   ･"
	@echo "  ﾟ☆  ﾟ｡ ✦    ･ ｡ ﾟ☆"
	@printf "$(RESET)"
endef

define show_libft_dream
	@echo "$(COSMIC_GOLD)$(BOLD)"
	@echo "╭─────────────────────────────────────────────────────────╮"
	@echo "│                                                         │"
	@echo "│    $(AURORA_PINK)✧･ﾟ: *✧･ﾟ:* $(STARLIGHT)LIBFT DREAMS$(AURORA_PINK) *:･ﾟ✧*:･ﾟ✧                  │"
	@echo "│                                                         │"
	@echo "│      $(MOONBEAM)Where Functions Come to Life 🌙                    │"
	@echo "│                                                         │"
	@echo "╰─────────────────────────────────────────────────────────╯$(RESET)"
	@echo ""
	@echo "$(DREAMY_CYAN)         💎 Crafting magical functions... 💎$(RESET)"
	@echo "$(DIM)$(AURORA_PURPLE)           ~ A library born from stardust ~$(RESET)"
	@echo ""
endef

# Progress tracking
TOTAL_SRCS = $(words $(SRCS))

define magical_progress
	@current_file=$(ls -1 *.o 2>/dev/null | wc -l); \
	current_file=$(($current_file + 1)); \
	printf "$(AURORA_GREEN)$(SPARKLE) Weaving magic into $(AURORA_YELLOW)$(notdir $<)$(AURORA_GREEN)... "; \
	stars=$(($current_file * 20 / $(TOTAL_SRCS))); \
	printf "$(COSMIC_GOLD)["; \
	for i in $(seq 1 $stars); do printf "$(STAR)"; done; \
	for i in $(seq $(($stars + 1)) 20); do printf "$(DIM)･$(RESET)"; done; \
	printf "$(COSMIC_GOLD)] %d/%d $(RAINBOW)$(RESET)\n" $current_file $(TOTAL_SRCS)
endef

define constellation_complete
	@echo ""
	@echo "$(AURORA_PINK)$(BOLD)    ･ﾟ✧*:･ﾟ✧ $(STARLIGHT)CONSTELLATION COMPLETE$(AURORA_PINK) ✧ﾟ･: *✧ﾟ･$(RESET)"
	@echo ""
	@echo "$(DREAMY_CYAN)         💎 Your library shimmers with power 💎$(RESET)"
	@echo "$(MOONBEAM)              $(NAME) has been born!$(RESET)"
	@echo ""
	$(call dream_sequence)
	@echo ""
endef

define cleaning_ritual
	@echo "$(AURORA_PURPLE)🌙 Performing cleansing ritual...$(RESET)"
	@echo "$(DIM)   Banishing old enchantments...$(RESET)"
	@sleep 0.5
	@echo "$(AURORA_BLUE)✨ The workspace grows pure$(RESET)"
endef

define purification_complete
	@echo "$(COSMIC_GOLD)💎 Purification complete - ready for new magic 💎$(RESET)"
endef

all: $(NAME)

#$(BUILD_DIR):
#	@mkdir -p $(addprefix $(BUILD_DIR)/, $(SRCS_DIRS))

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(AURORA_GREEN)✨ Compiling $(AURORA_YELLOW)$(notdir $<)$(AURORA_GREEN)...$(RESET)\n"
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@
	@printf "$(COSMIC_GOLD)⭐ Success!$(RESET)\n"

$(NAME): $(OBJS)
	$(call show_libft_dream)
	@echo "$(AURORA_YELLOW)$(BOLD)💎 Binding $(TOTAL_SRCS) functions into eternal harmony... 💎$(RESET)"
	@ar rcs $(NAME) $(OBJS)
	$(call constellation_complete)

clean:
	$(call cleaning_ritual)
	@rm -rf $(BUILD_DIR)
	@echo "$(AURORA_GREEN)✨ Object files dissolved into stardust$(RESET)"

fclean: clean
	@echo "$(AURORA_PURPLE)$(MOONBEAM) Complete purification in progress...$(RESET)"
	@rm -f $(NAME)
	$(call purification_complete)

re: fclean all

# Secret dream mode (run with: make dream)
dream:
	@echo "$(AURORA_PINK)$(BOLD)"
	@echo "    ✧･ﾟ: *✧･ﾟ:* ENTERING DREAM MODE *:･ﾟ✧*:･ﾟ✧"
	@echo ""
	@echo "$(DREAMY_CYAN)Your libft is more than code..."
	@echo "$(MOONBEAM)It's a constellation of possibilities$(RESET)"
	@echo ""
	$(call dream_sequence)
	@echo "$(COSMIC_GOLD)Functions flow like starlight through the void$(RESET)"
	@echo "$(AURORA_BLUE)Each compilation is a spell cast into reality$(RESET)"
	@echo ""
	@echo "$(STARLIGHT)$(BOLD)✨ Keep dreaming, keep coding ✨$(RESET)"

.PHONY: all clean fclean re dream
