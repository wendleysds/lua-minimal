CROSS_COMPILE ?=
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar

# Diretórios
SRC_DIR = ./src
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# Flags base
BASE_CFLAGS = -Wall -Werror -std=gnu11 -Isrc/include
BASE_CFLAGS += -Wno-unused-function -Wno-unused-parameter
BASE_CFLAGS += -Wno-int-to-pointer-cast -Wno-attribute-alias -Wno-cpp
BASE_CFLAGS += -O2 -fno-stack-protector -fno-common

ifdef DEBUG
BASE_CFLAGS += -g
endif

ifdef BIT32
BASE_CFLAGS += -m32
endif

FREESTANDING_FLAGS = -ffreestanding -nostdlib -nostartfiles

LDFLAGS = 

CORE_SRC = $(shell find $(SRC_DIR)/core -name "*.c")
LIB_SRC  = $(shell find $(SRC_DIR)/lib -name "*.c")

LUA_SRC  = $(SRC_DIR)/lua.c
LUAC_SRC = $(SRC_DIR)/luac.c

CORE_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(CORE_SRC))
LIB_OBJS  = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(LIB_SRC))

LUA_O  = $(OBJ_DIR)/lua.o
LUAC_O = $(OBJ_DIR)/luac.o

LUA_BIN        = $(BIN_DIR)/lua
LUAC_BIN       = $(BIN_DIR)/luac
LUA_MINIMAL_BIN = $(BIN_DIR)/lua-minimal

.PHONY: all clean lua-minimal

all: $(LUA_BIN) $(LUAC_BIN)

$(LUA_BIN): $(CORE_OBJS) $(LIB_OBJS) $(LUA_O)
	@echo "  LD     $@"
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^ -lm

$(LUAC_BIN): $(CORE_OBJS) $(LIB_OBJS) $(LUAC_O)
	@echo "  LD     $@"
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^ -lm

lua-minimal: CFLAGS := $(BASE_CFLAGS) $(FREESTANDING_FLAGS)
lua-minimal: $(LUA_MINIMAL_BIN)

$(LUA_MINIMAL_BIN): $(CORE_OBJS)
	@echo "  LD     $@ (freestanding)"
	@mkdir -p $(dir $@)
	$(CC) $(FREESTANDING_FLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "  CC     $<"
	@mkdir -p $(dir $@)
	$(CC) $(BASE_CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)