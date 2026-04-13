CC := cc
CFLAGS := -fPIE -Wall -Wextra -Werror -g
INCLUDES := -Iincludes -Ilib/libft -I./lib/minilibx-linux
SRC_DIR := src
BUILD_DIR := build
LIBFT_DIR := lib/libft
LIBFT := $(LIBFT_DIR)/libft.a

SRCS := \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/pixel.c \
	$(SRC_DIR)/sphere.c \
	$(SRC_DIR)/vec3.c \
	$(SRC_DIR)/parsing/parsing.c \
$(SRC_DIR)/parsing/parsing_init.c \
	$(SRC_DIR)/parsing/parsing_error.c \
	$(SRC_DIR)/parsing/parsing_utils.c \
	$(SRC_DIR)/parsing/parsing_pack.c \
	$(SRC_DIR)/parsing/parsing_primitives.c \
	$(SRC_DIR)/camera.c

OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

MLX = $(MLXDIR)/libmlx.a
MLXFLAGS = -lXext -lX11 -lm
MLXDIR = lib/minilibx-linux

NAME := minirt

LDFLAGS := -L$(LIBFT_DIR)
CFLAGS += -MMD -MP

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(MLX)
	$(CC) $(CFLAGS) $(MLXFLAGS) -o $@ $(OBJS) $(LDFLAGS) -lft $(LDLIBS) $(MLX)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX):
	@make -C $(MLXDIR) --no-print-directory

clean:
	rm -rf $(BUILD_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re