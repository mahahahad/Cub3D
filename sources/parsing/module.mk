PARSING_SRCS := $(addprefix $(SRCS_DIR)/parsing/, read_map.c read_map_utils.c validate_map.c validate_map_utils.c check_boundary.c save_textures.c)

SRCS += $(PARSING_SRCS)
