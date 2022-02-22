# Configuration used to compile a vm program.
# This configuration is used by the Makefile to compile a vm program.
CC = gcc
CFLAGS = -g -Wall -Werror -std=c99
OBJECTS_DIR = obj
SRC_DIR = src

# Compile to executable
all: $(OBJECTS_DIR)/vm.o
	$(CC) $(CFLAGS) -o main.exe $(OBJECTS_DIR)/vm.o

# Compile all the .c files in the src directory.
obj: $(OBJECTS_DIR)
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) -o $(OBJECTS_DIR)/vm.o $(SRC_DIR)/vm.c
	
# Compile a single .c file.
%.o: %.c
	@mkdir -p $(OBJECTS_DIR)
	@$(CC) $(CFLAGS) -o $(OBJECTS_DIR)/$@ $(SRC_DIR)/$@

# Clean up the object files.
clean:
	@rm -rf $(OBJECTS_DIR)