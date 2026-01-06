# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g
LDFLAGS =

# Directories
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = test

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)

# Object files
# Exclude main.o from the list of objects for the test build
ALLOCATOR_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(filter-out $(SRC_DIR)/main.c, $(SRCS)))
MAIN_OBJ = $(patsubst $(SRC_DIR)/main.c, $(BUILD_DIR)/main.o, $(filter $(SRC_DIR)/main.c, $(SRCS)))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(TEST_SRCS))

# Executables
MAIN_EXEC = $(BUILD_DIR)/main
TEST_EXEC = $(BUILD_DIR)/test_allocator

.PHONY: all clean test run_tests

all: $(MAIN_EXEC) $(TEST_EXEC)

# Rule to build the main executable
$(MAIN_EXEC): $(ALLOCATOR_OBJS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Rule to build the test executable
$(TEST_EXEC): $(ALLOCATOR_OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile test files into object files
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Target to run tests
run_tests: $(TEST_EXEC)
	./$(TEST_EXEC)

# Target to clean the build directory
clean:
	rm -rf $(BUILD_DIR)
