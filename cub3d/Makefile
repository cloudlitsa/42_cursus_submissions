NAME = cub3D
BONUS_NAME = cub3D_bonus

# use make BONUS=1 to compile bonus version
ifeq ($(BONUS), 1)
	NAME = $(BONUS_NAME)
endif

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
DEPFLAGS = -MMD -MP

INCLUDES = -I includes -I libft/includes
INCLUDES_BONUS = -I includes_bonus -I libft/includes

ifeq ($(BONUS), 1)
	INCLUDES = $(INCLUDES_BONUS)
endif

LIBFT = ./libft/libft.a
MLX_PATH_LINUX = ./minilibx
MLX_PATH_MAC = ./minilibx_opengl
FRAMEWORKS_MAC = -framework OpenGL -framework AppKit
FRAMEWORKS_LINUX = -L ./minilibx -lmlx -lmlx_Linux -L/usr/lib/X11 -lXext -lX11 -lm
SRCS = srcs/main.c \
	srcs/game/draw_background.c srcs/game/end_of_game.c srcs/game/render_new_frame.c srcs/game/start_game.c \
	srcs/init/graphics_init.c srcs/init/init.c \
	srcs/input/handle_input.c srcs/input/keyboard.c srcs/input/mouse.c srcs/input/moves.c srcs/input/rotates.c \
	srcs/minimap/minimap_ray.c srcs/minimap/minimap.c \
	srcs/parse/parser1.c srcs/parse/parser2.c srcs/parse/parser3.c srcs/parse/parser4.c srcs/parse/parser5.c srcs/parse/parser6.c srcs/parse/parser7.c \
	srcs/raycasting/raycasting.c srcs/raycasting/draw_wall_line.c srcs/raycasting/calculate_wall_dist.c \
	srcs/utils/utils1.c srcs/utils/utils2.c srcs/utils/utils3.c
SRCS_BONUS = srcs_bonus/main_bonus.c \
	srcs_bonus/door/doors_bonus.c \
	srcs_bonus/game/draw_background_bonus.c srcs_bonus/game/end_of_game_bonus.c srcs_bonus/game/render_new_frame_bonus.c srcs_bonus/game/start_game_bonus.c \
	srcs_bonus/init/graphics_init_bonus.c srcs_bonus/init/init_bonus.c \
	srcs_bonus/input/handle_input_bonus.c srcs_bonus/input/keyboard_bonus.c srcs_bonus/input/mouse_bonus.c srcs_bonus/input/moves_bonus.c srcs_bonus/input/rotates_bonus.c \
	srcs_bonus/minimap/minimap_ray_bonus.c srcs_bonus/minimap/minimap_bonus.c \
	srcs_bonus/parse/parser_doors_bonus.c srcs_bonus/parse/parser1_bonus.c srcs_bonus/parse/parser2_bonus.c srcs_bonus/parse/parser3_bonus.c srcs_bonus/parse/parser4_bonus.c srcs_bonus/parse/parser5_bonus.c srcs_bonus/parse/parser6_bonus.c srcs_bonus/parse/parser7_bonus.c \
	srcs_bonus/raycasting/calculate_wall_dist_bonus.c srcs_bonus/raycasting/draw_wall_line_bonus.c srcs_bonus/raycasting/raycasting_bonus.c srcs_bonus/raycasting/dda_doors_bonus.c srcs_bonus/raycasting/draw_wall_line_utils_bonus.c \
	srcs_bonus/utils/utils1_bonus.c srcs_bonus/utils/utils2_bonus.c srcs_bonus/utils/utils3_bonus.c

ifeq ($(BONUS), 1)
	SRCS = $(SRCS_BONUS)
endif

OBJ = $(SRCS:.c=.o)
OBJ_BONUS = $(SRCS_BONUS:.c=.o)
DEPS = $(SRCS:.c=.d)
ALL_DEPS = $(SRCS:.c=.d) $(SRCS_BONUS:.c=.d)
RM = rm -f
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	FRAMEWORKS = $(FRAMEWORKS_MAC)
	MLX_PATH = $(MLX_PATH_MAC)
else ifeq ($(UNAME), Linux)
	FRAMEWORKS = $(FRAMEWORKS_LINUX)
	MLX_PATH = $(MLX_PATH_LINUX)
endif

MLX = $(MLX_PATH)/libmlx.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX) $(FRAMEWORKS)

$(LIBFT):
	@make -C libft

$(MLX):
	@make -C $(MLX_PATH)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -c $< -o $@

bonus:
	$(MAKE) BONUS=1
-include $(DEPS)

clean:
	@$(RM) $(OBJ) $(OBJ_BONUS) $(ALL_DEPS)
	@make -C libft clean
	@make -C $(MLX_PATH) clean

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re bonus