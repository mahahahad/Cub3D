PARSING_SRCS := $(addprefix $(SRCS_DIR)/parsing/, read_map.c read_map_utils.c validate_map.c check_boundary.c)

SRCS += $(PARSING_SRCS)
