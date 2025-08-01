# Project details
PROJECT := arena_alloc
CC := $(shell command -v clang || command -v gcc)
CFLAGS := -Wall -Wextra -Werror -Wconversion -Wunused-result
CPPFLAGS := -Isrc -Iinclude

# Dirs
BUILD_DIR := build
TEST_SRC_DIR := test
SRC_DIR := src
INC_DIR := include
OBJ_DIR := $(BUILD_DIR)/obj
TEST_OBJ_DIR := $(BUILD_DIR)/test-obj

# Files
SRC := $(wildcard $(SRC_DIR)/*.c)
INC := $(INC_DIR)/$(PROJECT).h
TEST_MAIN := $(TEST_SRC_DIR)/main/test.c
TEST_SRC := $(wildcard $(TEST_SRC_DIR)/*.c)

# Targets
LIB_SO := $(BUILD_DIR)/lib$(PROJECT).so
LIB_A := $(BUILD_DIR)/lib$(PROJECT).a
TEST_EXE := $(BUILD_DIR)/$(PROJECT)_test
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_OBJ := $(TEST_SRC:$(TEST_SRC_DIR)/%.c=$(TEST_OBJ_DIR)/%.o)

# Rules
.PHONY: default test clean install uninstall

default: $(LIB_A) $(LIB_SO) | $(BUILD_DIR)

test: $(TEST_EXE)
	./$^

clean:
	rm -rf $(BUILD_DIR) compile_commands.json

install: $(LIB_A) $(LIB_SO) $(INC)
	install -m 644 $(INC) /usr/local/include/$(notdir $(INC))
	install -m 644 $(LIB_SO) /usr/local/lib/$(notdir $(LIB_SO))
	install -m 644 $(LIB_A) /usr/local/lib/$(notdir $(LIB_A))

uninstall:
	rm $(addprefix /usr/local/include/, $(notdir $(INC)))
	rm $(addprefix /usr/local/lib/, $(notdir $(LIB_A)))
	rm $(addprefix /usr/local/lib/, $(notdir $(LIB_SO)))

$(LIB_A): $(OBJ) $(INC) | $(BUILD_DIR)
	ar rcs $@ $<

$(LIB_SO): $(OBJ) $(INC) | $(BUILD_DIR)
	$(CC) -shared $(CFLAGS) $(CPPFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/*.h $(INC) | $(OBJ_DIR)
	$(CC) -c -fPIC $(CFLAGS) $(CPPFLAGS) $< -o $@

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c $(TEST_SRC_DIR)/*.h | $(OBJ_DIR) $(TEST_OBJ_DIR)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(TEST_EXE): $(TEST_MAIN) $(TEST_OBJ) $(OBJ) | $(BUILD_DIR)
	bear -- $(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(BUILD_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

$(TEST_OBJ_DIR):
	mkdir -p $@
