CC := cc
CFLAGS := -Wall -Werror -Wextra
NAME := cub3D
INCLUDES := -Iincludes

SRCS_DIR := sources
OBJS_DIR := objects
SUB_DIRS := $(shell find $(SRCS_DIR) -type d -print)
UTILS_DIR := $(SRCS_DIR)/utils

MODULES := $(UTILS_DIR) 

SRCS := $(addprefix $(SRCS_DIR)/, cub3D.c)

include $(patsubst %, %/module.mk, $(MODULES))

OBJS := $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(patsubst $(SRCS_DIR)%, $(OBJS_DIR)%, $(SUB_DIRS))

bonus:

re: fclean all

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

.PHONY: all bonus clean fclean re 
