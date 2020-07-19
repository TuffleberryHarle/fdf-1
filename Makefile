NAME = fdf

CC = gcc
FLAGS = -Wall -Werror -Wextra -O3

LIBS = -lmlx -lm -lft -L$(LIBFT_DIR) -L$(MINILIBX_DIR) -framework OpenGL -framework AppKit
INCS = -I$(H_DIR) -I$(LIBFT_H) -I$(MINILIBX_H)

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = ./libft/
LIBFT_H = $(LIBFT_DIR)includes/

MINILIBX = $(MINILIBX_DIR)libmlx.a
MINILIBX_DIR = ./minilibx_macos/
MINILIBX_H = $(MINILIBX_DIR)

H_LIST = fdf.h\
	color.h\
	key_macos.h\
	error_message.h
H_DIR = ./includes/
H = $(addprefix $(H_DIR), $(H_LIST))

SRCS_DIR = ./sources/
SRCS_LIST = main.c\
	colour.c\
	controls.c\
	converter.c\
	draw.c\
	initializations.c\
	keyboard.c\
	map_reader.c\
	menu.c\
	mouse.c\
	options.c\
	other_funcs_1.c\
	other_funcs_2.c\
	projections.c\
	stack_reader.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJ_DIR = objects/
OBJ_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJ	= $(addprefix $(OBJ_DIR), $(OBJ_LIST))

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) OBJ_DIR OBJ
	@$(CC) $(FLAGS) $(LIBS) $(INCS) $(OBJ) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)object files have been created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME)'s been created$(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(NAME): $(GREEN)$(OBJ_DIR)'s been created$(RESET)"

$(OBJ_DIR)%.o : SRCS_DIR%.c H
	@$(CC) $(FLAGS) -c $(INCS) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIR)

$(MINILIBX):
	@echo "$(NAME): $(GREEN)Creating $(MINILIBX)...$(RESET)"
	@$(MAKE) -sC $(MINILIBX_DIR)

clean:
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@$(MAKE) -sC $(MINILIBX_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME): $(RED)$(OBJ_DIR)'s been deleted$(RESET)"
	@echo "$(NAME): $(RED)object files have been deleted$(RESET)"

fclean: clean
	@rm -f $(MINILIBX)
	@echo "$(NAME): $(RED)$(MINILIBX)'s been deleted$(RESET)"
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT)'s been deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME)'s been deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all