CC= cc -Werror -Wextra -Wall -I. -g3

SRC= main.c \
	destroy.c \
	init.c \
	monitor.c \
	routine.c \
	utils.c \
	validator.c

O_DIR= obj/
OBJ= $(SRC:%.c=$(O_DIR)%.o)

NAME= philo

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
	@echo -n "\033[32m\nSuccessfully Generated \033[0mPhilo \n\n"

$(O_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@echo "\033[95mCompiling\033[0m $(notdir $<)"
	@sleep 0.0001
	@$(CC) -c $< -o $@


clean:
	@echo "\033[95mCleansing Philo Objects"
	@sleep 0.7
	@echo -n "."
	@sleep 0.2
	@echo -n "."
	@sleep 0.2
	@echo ".\033[0m"
	@sleep 0.2
	@rm -rf $(O_DIR)

fclean:
	@echo "\033[95mCleansing Philo"
	@sleep 0.7
	@echo -n "."
	@sleep 0.2
	@echo -n "."
	@sleep 0.2
	@echo ".\033[0m"
	@sleep 0.2
	@rm -rf $(O_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean