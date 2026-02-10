CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lSDL2
TARGET = bouncy
SRC = bouncy.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
