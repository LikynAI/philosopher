# executable
PHILO = philo

# sources
_SRC = main.c states.c philosophers.c utils.c
SRC_DIR = sources
SRC = $(_SRC:%=$(SRC_DIR)/%)
# tmp files
OBJ_DIR = tmp_files
OBJ = $(SRC:%.c=%.o)
DPS = $(SRC:%.c=%.d)

# headers
HEADS = philosophers.h

# Make commands
GCC = gcc
GCC_FLAGS = -O2 -Wall -Wextra -Werror
RM = rm -f

# rules
all: $(PHILO)


%.o: %.c Makefile
	$(GCC) $(GCC_FLAGS) -MMD -MP -c $< -o $@

$(PHILO): $(OBJ)
	$(GCC) -pthread $(OBJ) -o $@

clean:
	$(RM) $(OBJ) $(DPS) $(PHILO)

fclean: clean
	$(RM) philo

re: fclean all

-include $(DPS)

.PHONY: all re clean compile_libs