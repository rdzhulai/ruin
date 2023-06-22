# Define variables
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wconversion  -Werror
LIBS = -lm
SRC_DIR = .
OBJ_DIR = .
BIN_DIR = .
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
EXECUTABLE = $(BIN_DIR)/ps5

# Define phony targets
.PHONY: all clean

# Define rule to build executable
$(EXECUTABLE): $(OBJECTS)
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c 
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

# Define rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Define rule to create obj directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Define all target
all: $(EXECUTABLE)

# Define clean target
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE)

# Use include statement to include additional Makefile
# include other_makefile.mk
