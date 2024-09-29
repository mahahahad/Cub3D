SETUP_SRCS := $(addprefix $(SRCS_DIR)/setup/, check_args.c init_structs.c init_images.c init_handlers.c handlers.c)

SRCS += $(SETUP_SRCS)
