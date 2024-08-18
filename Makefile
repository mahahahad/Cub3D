CC := cc
CFLAGS := -Wall -Werror -Wextra
OBJS := cub3d.c

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)


