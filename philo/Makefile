# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kebris-c <kebris-c@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/08 13:07:54 by kebris-c          #+#    #+#              #
#    Updated: 2025/10/03 19:03:16 by kebris-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

.DEFAULT:
	@echo ""
	@echo "❌ Unknown target: '$@'"
	@echo "If you want to know what rules are available and "
	@echo "what the hell they do, then run: make help"
	@echo ""

.PHONY: all bonus clean fclean re re_bonus setup help rigor rigor_bonus norm \
	leaks leaks_bonus

# 📚 Basic project variables
#
PROJECT		= philo
P_BONUS		= $(PROJECT)_bonus
NAME		= $(PROJECT).a
N_BONUS		= $(P_BONUS).a

# 🔧 Compiler and flags
#
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
CEXTRAFLAGS	= \
			$(CFLAGS) \
			-MMD \
			-MP \
			-std=c17 \
			-Wpedantic \
			-Wconversion \
			-Wsign-conversion \
			-Wshadow \
			-Wstrict-prototypes \
			-Wpointer-arith \
			-Wcast-align \
			-Wunreachable-code \
			-Winit-self \
			-Wswitch-enum \
			-Wfloat-equal \
			-Wformat=2 \
			-Wmissing-prototypes \
			-Wmissing-declarations \
			-Wdouble-promotion \
			-Wundef \
			-Wbad-function-cast \
			-Winline -Wvla \
			-Wno-unused-parameter \
			-Wno-missing-field-initializers \
			-fstrict-aliasing \
			-fstack-protector-strong \
			-D_FORTIFY_SOURCE=2 \
			-g3 \
			-O0

# 🔨 Tools
#
AR      = ar rcs
RM      = rm -rf
NORM    = norminette
CP      = cp -r
LS		= ls -l

# 📂 Fast path variables / dirs
#
SRC_DIR		= src/
INCL_DIR	= include/
OBJS_DIR	= objs/
DEPS_DIR	= deps/
# If there is bonus
#
BONUS_DIR		= bonus/
B_SRC_DIR		= bonus/src/
B_INCL_DIR		= bonus/include/
B_OBJS_DIR		= bonus/objs/
B_DEPS_DIR		= bonus/deps/
# If there is Libft
#
LIB_DIR			= libft/
L_SRC_DIR		= libft/src/
L_INCL_DIR		= libft/include/
L_OBJS_DIR		= libft/objs/
L_DEPS_DIR		= libft/deps/

# 🎯 Objects and Deps
#
SRCS	= $(notdir $(wildcard $(SRC_DIR)*.c))
OBJS	= $(patsubst %.c,$(OBJS_DIR)%.o,$(SRCS))
DEPS	= $(patsubst $(OBJS_DIR)%.o,$(DEPS_DIR)%.d,$(OBJS))
# If there is bonus
#
B_SRCS	= $(notdir $(wildcard $(B_SRC_DIR)*.c))
B_OBJS	= $(patsubst %.c,$(B_OBJS_DIR)%.o,$(B_SRCS))
B_DEPS	= $(patsubst $(B_OBJS_DIR)%.o,$(B_DEPS_DIR)%.d,$(B_OBJS))

# 📄 Headers. First, we need to check if there is a libft dir
#
HAS_LIBFT = $(shell \
    if [ -d libft ]; then \
        echo yes; \
    else \
        echo no; \
    fi)
HEADERS = -I$(INCL_DIR)
ifeq ($(HAS_LIBFT),yes)
    HEADERS += -I$(L_INCL_DIR)
endif

# ------------------------------------------------ #
#    COMPILE COMMANDS 			                   #
# ------------------------------------------------ #

define COMPILE_PROJECT
	@if $(NORM) $(SRC_DIR) 2>/dev/null; then \
		if [ -d $(LIB_DIR) ]; then \
			$(CC) $(1) $(2) $(HEADERS) -L$(LIB_DIR) -lft -o $(3); \
		else \
			$(CC) $(1) $(2) $(HEADERS) -o $(3); \
		fi; \
	else \
		exit 1; \
	fi
endef

# ------------------------------------------------ #
#  Setup rule: normalize project structure         #
# ------------------------------------------------ #

setup:
	@mkdir -p $(SRC_DIR) $(INCL_DIR) $(OBJS_DIR) $(DEPS_DIR)
	@if [ -d $(BONUS_DIR) ]; then \
		mkdir -p $(B_SRC_DIR) $(B_INCL_DIR) $(B_OBJS_DIR) $(B_DEPS_DIR); \
		find . -maxdepth 1 -name "*_bonus.c" ! -path "./$(B_SRC_DIR)*" -exec mv -n {} $(B_SRC_DIR)/ \;; \
		find . -maxdepth 1 -name "*_bonus.h" ! -path "./$(B_INCL_DIR)*" -exec mv -n {} $(B_INCL_DIR)/ \;; \
		find . -maxdepth 1 -name "*_bonus.o" ! -path "./$(B_OBJS_DIR)*" -exec mv -n {} $(B_OBJS_DIR)/ \;; \
		find . -maxdepth 1 -name "*_bonus.d" ! -path "./$(B_DEPS_DIR)*" -exec mv -n {} $(B_DEPS_DIR)/ \;; \
	fi
	@find . -maxdepth 1 -name "*.c" ! -path "./$(SRC_DIR)*" -exec mv -n {} $(SRC_DIR)/ \;
	@find . -maxdepth 1 -name "*.h" ! -path "./$(INCL_DIR)*" -exec mv -n {} $(INCL_DIR)/ \;
	@find . -maxdepth 1 -name "*.o" ! -path "./$(OBJS_DIR)*" -exec mv -n {} $(OBJS_DIR)/ \;
	@find . -maxdepth 1 -name "*.d" ! -path "./$(DEPS_DIR)*" -exec mv -n {} $(DEPS_DIR)/ \;

# ------------------------------------------------ #
#  Help rule: Be user-friendly			           #
# ------------------------------------------------ #
# Make sure this rule is updated with correct data
#
help:
	@echo ""
	@echo "==================== HELP ===================="
	@echo ""
	@echo "Try to run make followed by one of the following rule you want"
	@echo "Example: make clean"
	@echo ""
	@echo "📦 Basic build:"
	@echo "  all           -> setup, build $(NAME). Default option used by make"
	@echo "  bonus         -> build $(N_BONUS) with bonus sources"
	@echo "  clean         -> remove object and dependency files"
	@echo "  fclean        -> clean + remove $(NAME) or $(N_BONUS), objs dir, deps dir and executable"
	@echo "  re            -> fclean + all"
	@echo "  re_bonus      -> fclean + bonus"
	@echo ""
	@echo "⚡ Project compilation:"
	@echo "  $(PROJECT)			-> compile main project"
	@echo "  bonus_$(PROJECT)	-> compile bonus project"
	@echo "  rigor				-> compile main project with rigurous flags"
	@echo "  bonus_rigor		-> compile bonus project with rigurous flags"
	@echo ""
	@echo "🛠 Norminette, leaks & extra features:"
	@echo "  norm          -> run norminette on project"
	@echo "  leaks         -> run valgrind on project"
	@echo "  leaks_bonus   -> run valgrind on bonus project"
	@echo "  setup         -> Normalize project dirs setup"
	@echo ""
	@echo "==============================================="
	@echo ""

#------------------------------------------------#
#   BASIC RULES / LIBRARY COMMANDS               #
#------------------------------------------------#

all: setup $(NAME) $(PROJECT)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "✅ $(NAME) built with main sources"

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@echo "🔨 Compiling $<..."
	@if [ -d $(LIB_DIR) ]; then \
		$(MAKE) -C $(LIB_DIR); \
	fi
	@$(MAKE) -C $(MLBX);
	@$(CC) $(CFLAGS) -MMD -MP $(HEADERS) -c $< -o $@
	@mv $(OBJS_DIR)$*.d $(DEPS_DIR)

bonus: setup $(N_BONUS) $(P_BONUS)

$(N_BONUS): $(B_OBJS)
	@$(AR) $(N_BONUS) $(B_OBJS)
	@echo "✅ $(N_BONUS) build with bonus sources";

$(B_OBJS_DIR)%.o: $(B_SRC_DIR)%.c
	@echo "🔨 Compiling bonus $<..."
	@if [ -d $(LIB_DIR) ]; then \
		$(MAKE) -C $(LIB_DIR); \
	fi
	@$(MAKE) -C $(MLBX);
	@$(CC) $(CFLAGS) -MMD -MP $(HEADERS) -c $< -o $@
	@mv $(B_OBJS_DIR)$*.d $(B_DEPS_DIR)

clean:
	@$(RM) $(OBJS) $(B_OBJS) $(DEPS) $(B_DEPS)

fclean: clean
	@$(RM) $(NAME) $(N_BONUS) $(PROJECT) $(P_BONUS) $(OBJS_DIR) \
		$(DEPS_DIR) $(B_OBJS_DIR) $(B_DEPS_DIR)

re: fclean all

re_bonus: fclean bonus

#------------------------------------------------#
#   PROJECT COMPILATION                          #
#------------------------------------------------#

$(PROJECT): $(OBJS)
	$(call COMPILE_PROJECT,$(CFLAGS),$(OBJS),$(PROJECT))

$(PROJECT)_bonus: $(B_OBJS)
	$(call COMPILE_PROJECT,$(CFLAGS),$(B_OBJS),$(P_BONUS))

rigor: $(OBJS)
	$(call COMPILE_PROJECT,$(CEXTRAFLAGS),$(OBJS),$(BONUS))
    
rigor_bonus: $(B_OBJS)
	$(call COMPILE_PROJECT,$(CEXTRAFLAGS),$(B_OBJS),$(P_BONUS))

#------------------------------------------------#
#   NORMINETTE & LEAKS                           #
#------------------------------------------------#

norm:
	@if $(NORM) $(CURDIR) 2>/dev/null; then \
		exit 0; \
	else \
		exit 1; \
	fi

leaks: $(PROJECT)
	@valgrind --leak-check=full --show-leak-kinds=all ./$(PROJECT) || true

leaks_bonus: $(P_BONUS)
	@valgrind --leak-check=full --show-leak-kinds=all ./$(PROJECT) || true

# Include dependency files if they exist
#
-include $(wildcard $(DEPS))
-include $(wildcard $(B_DEPS))

# Dinamic version of .PHONY
#
#.PHONY: $(filter-out $(NAME) $(PROJECT) bonus_$(PROJECT), $(MAKECMDGOALS))