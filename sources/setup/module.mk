SETUP_SRCS := $(addprefix $(SRCS_DIR)/setup/, check_args.c init_structs.c handlers.c render.c raycasting.c texture.c raycasting_utils.c)

SRCS += $(SETUP_SRCS)
