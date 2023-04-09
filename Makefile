CC = cc
CFLAGS = -Wall -Wextra -Werror -flto -Ofast
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LDFLAGS = -lmlx -lXext -lX11 -lm -lbsd 
endif
ifeq ($(UNAME_S),Darwin)
	LDFLAGS = -lmlx -framework OpenGL -framework AppKit -flto -Ofast
endif
LDFLAGS += -fsanitize=address

BUILD_DIR = build
INC = -I./inc -I/usr/local/include
HEADER_FILES = minirt.h camera.h vector.h shape.h parse.h get_next_line.h light.h 
INCLUDES = $(addprefix inc/, $(HEADER_FILES))
FILES = main.o render.o camera.o vec.o vec_adding.o vec_multipliying.o shapes/sphere.o shapes/plane.o shapes/cylinder.o shapes/cap.o shapes/lists.o utils.o light.o\
		parse/parse.o parse/parse_shape.o parse/str.o parse/utils.o parse/gnl/get_next_line.o parse/gnl/get_next_line_utils.o debug.o quit.o
OBG = $(addprefix $(BUILD_DIR)/, $(FILES))

NAME = miniRT

all: $(NAME)

$(NAME): $(OBG)
	$(CC) $^ -o $@ $(LDFLAGS) -fsanitize=address

$(BUILD_DIR)/%.o: src/%.c $(INCLUDES)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBG)
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
