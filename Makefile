CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunused -g #-fsanitize=address
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LDFLAGS = -lmlx -lXext -lX11 -lm -lbsd
endif
ifeq ($(UNAME_S),Darwin)
	LDFLAGS = -lmlx -framework OpenGL -framework AppKit
endif
#LDFLAGS += -fsanitize=address

BUILD_DIR = build
#HEADER_FILES = 
INCLUDES = $(addprefix inc/, $(HEADER_FILES))
INC = -I inc -I/usr/local/include
FILES = main.o render.o camera.o vec.o vec_multipliying.o shapes/sphere.o shapes/plane.o shapes/cylinder.o shapes/lists.o utils.o light.o\
		parse/parse.o parse/str.o parse/utils.o parse/gnl/get_next_line.o parse/gnl/get_next_line_utils.o debug.o
OBG = $(addprefix $(BUILD_DIR)/, $(FILES))

NAME = miniRT

all: $(NAME)

$(NAME): $(OBG)
	$(CC) $^ -o $@ $(LDFLAGS) #-fsanitize=address

$(BUILD_DIR)/%.o: src/%.c #$(INCLUDES)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBG)
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
