CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lSDL2

TARGET = plot
SRC = plot.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
