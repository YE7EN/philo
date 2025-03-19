NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g

SRC =	src/main.c \
		src/init.c \
		src/utils.c \
		src/utils_2.c \
		src/routine.c\
		src/monitor.c\



INC = includes
OBJ_DIR = .obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:src/%.c=%.o))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "philo's ready to eat, sleep, think... or die"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@echo "Compiling $(notdir $<)..."
	@$(CC) $(CFLAGS) -I$(INC) -o $@ -c $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "Cleaning libraries and executable..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
