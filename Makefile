C = gcc

CFLAGS = -Wall -Wextra -std=c++11 -lstdc++

TARGET = test

BIN_DIR = bin

SRCS = main.cpp

OBJS = $(SRCS:.c=.o)

all: | $(BIN_DIR) $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
$(BIN_DIR):
	mkdir -p $(BIN_DIR)
clean:
	rm -f $(OBJS) $(BIN_DIR)/$(TARGET)
	rmdir $(BIN_DIR) 2>dev>null || true
