CC := cc
CFLAGS := -Wall -Werror -Wextra
NAME := cub3D
INCLUDES := -Iincludes

SRCS_DIR := sources
OBJS_DIR := objects
SUB_DIRS := $(shell find $(SRCS_DIR) -type d -print)
UTILS_DIR := $(SRCS_DIR)/utils

MODULES := $(UTILS_DIR) 

include $(patsubst %, %/module.mk, $(MODULES))

SRCS += $(addprefix $(SRCS_DIR)/, cub3D.c)

OBJS := $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

UNAME := $(shell uname -s)

ifeq ($(UNAME), Linux)
	MLX_DIR := mlx_Linux
	MLX_FLAGS += -lX11 -lXext
	INCLUDES += -I$(MLX_DIR)
endif
MLX := $(MLX_DIR)/lib$(MLX_DIR).a

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(MLX) $(MLX_FLAGS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(patsubst $(SRCS_DIR)%, $(OBJS_DIR)%, $(SUB_DIRS))

$(MLX):
	@make -s -C $(MLX_DIR)

bonus:

re: fclean all

clean:
	@rm -rf $(OBJS_DIR)
	@make -s -C $(MLX_DIR) clean

fclean: clean
	@rm -rf $(NAME)

.PHONY: all bonus clean fclean re 
