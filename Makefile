# Define colors using tput
BLACK = $(shell tput setaf 0)
RED = $(shell tput setaf 1)
GREEN = $(shell tput setaf 2)
YELLOW = $(shell tput setaf 3)
BLUE = $(shell tput setaf 4)
MAGENTA = $(shell tput setaf 5)
CYAN = $(shell tput setaf 6)
WHITE = $(shell tput setaf 7)
RESET_COLOR = $(shell tput sgr0)


# Define styles for text
BOLD = $(shell tput bold)
ITALIC = $(shell tput sitm)

# Define Emojis
CHECK = ✅
CROSS = ❌


# Proram name
NAME = Cub3D


# Shortcuts for objects, sources and header files
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS = $(addprefix $(OBJS_DIR)/, $(OBJS_FILES))
INCS = $(addprefix $(INCS_DIR)/, $(INCS_FILES)) $(LIBFT)


# All Directories
OBJS_DIR = .objs
SRCS_DIR = srcs
INCS_DIR = includes


# All sources so *.c files and 
# all objects files so *.o and 
# includes files so *.h
OBJS_FILES = $(SRCS_FILES:%.c=%.o)

SRCS_FILES = main.c \
			 parsing.c \
			 init.c \
			 utils.c \
			 parsing_utils.c \
			 check_file.c \
			 modify_map.c \
			 display.c \
			 color.c \
			 player_utils.c \
			 hooks.c \
			 free.c \
			 movements.c \
			 map_utils.c \
			 rays_utils.c \
			 rays.c \
			 read_file.c

INCS_FILES = cub3D.h \
			 msg.h 

# libft is my library, mlx is the school's library
LIBFT = libft/libft.a
MLX = mlx/libmlx.a

# All compilation flags
CFLAGS = -Wall -Wextra -Werror -g3 -O3 #Useful flags: -g3 -fsanitize=address
MLXFLAGS = -lX11 -lXext -lm #-Lmlx -lmlx -lX11 -lXext -lm -Lminilibx-linux -framework OpenGL -framework AppKit
IFLAGS = -I includes \
		 -I libft \
		 -I mlx

# Compiler to use
CC = cc
CLANG = clang

# All rules
all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS) $(INCS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)
	@echo "\n$(GREEN)$(NAME) created$(CHECK)$(RESET_COLOR)"

$(OBJS_DIR)/%.o:  $(SRCS_DIR)/%.c $(INCS)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $(word 1,$^) -o $@
	@echo "$(CYAN) $@ created$(RESET)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@echo "$(GREEN)$@ created$(CHECK)$(RESET_COLOR)"

$(LIBFT):
	@make -C ./libft -s

$(MLX):
	@make -C ./mlx -s
	@echo "$(GREEN)$@ created$(CHECK)$(RESET_COLOR)"

norm:
	@norminette includes srcs

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(RESET_COLOR)$(RED)$(OBJS_DIR) removed$(CROSS)$(RESET_COLOR)"
	@make clean -C ./libft -s
	@make clean -C ./mlx -s

fclean: clean
	@rm -rf $(NAME)
	@echo "$(RED)$(NAME) removed$(CROSS)$(RESET_COLOR)"
	@make fclean -C ./libft -s

re: fclean all

.PHONY: all clean fclean re