CC := cc
CFLAGS := -Wall -Werror -Wextra -g3
NAME := cub3D
INCLUDES := -Iincludes

SRCS_DIR := sources
OBJS_DIR := objects
SUB_DIRS := $(shell find $(SRCS_DIR) -mindepth 1 -type d -print)
MODULES := $(SUB_DIRS)

include $(patsubst %, %/module.mk, $(MODULES))

SRCS += $(addprefix $(SRCS_DIR)/, handlers.c cub3D.c)

OBJS := $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

UNAME := $(shell uname -s)

BGREEN := \033[1;32m
BYELLOW := \033[1;33m
BRED := \033[1;31m
ITALIC := \033[3m
RESET := \033[0m\033[K

all: $(NAME)

# Include the appropriate MLX library (based on your OS)
ifeq ($(UNAME), Darwin)
MLX_DIR := mlx_Darwin
MLX_FLAGS += -framework OpenGL -framework AppKit
MLX := libmlx.dylib
$(MLX):
	@echo "\n$(BYELLOW)Making MLX Library$(RESET)"
	@make -s -C $(MLX_DIR)
	@cp $(MLX_DIR)/libmlx.dylib .
	@echo "$(BGREEN)Made MLX Library$(RESET)\n"
else
MLX_DIR := mlx_Linux
MLX_FLAGS += -lX11 -lXext
MLX := $(MLX_DIR)/lib$(MLX_DIR).a
$(MLX):
	@echo "\n$(BYELLOW)Making MLX Library$(RESET)"
	@make -s -C $(MLX_DIR)
	@echo "$(BGREEN)Made MLX Library$(RESET)\n"
endif
INCLUDES += -I$(MLX_DIR)

$(NAME): $(OBJS) $(MLX)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "$(BGREEN)$(ITALIC)Cub3D ready to play!$(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(BGREEN)Created" $@ "$(RESET)"

$(OBJS_DIR):
	@mkdir -p $(patsubst $(SRCS_DIR)%, $(OBJS_DIR)%, $(SUB_DIRS))

bonus:

re: fclean all

clean:
	@echo "$(BRED)Deleting object files$(RESET)"
	@rm -rf $(OBJS_DIR)
	@make -s -C $(MLX_DIR) clean

fclean: clean
	@echo "$(BRED)Deleting library and executable$(RESET)\n"
	@rm -rf $(NAME)*
ifeq ($(UNAME), Darwin)
	@rm -rf libmlx.dylib
endif

debug: $(MLX)
	@$(CC) $(CFLAGS) $(INCLUDES) -g3 -fsanitize=address $(SRCS) $(MLX) $(MLX_FLAGS) -o $(NAME)_debug
	@echo "$(BYELLOW)Made Cub3D DEBUG$(RESET)"

.PHONY: all bonus clean fclean re debug
