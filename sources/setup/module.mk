SETUP_SRCS := $(addprefix $(SRCS_DIR)/setup/, init_structs.c check_args.c render.c raycasting.c texture.c raycasting_utils.c)

SRCS += $(SETUP_SRCS)
