CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lSDL2 -lm

TARGET = plot
SRC = plot.c tinyexpr.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

%.o: %.c tinyexpr.h
	$(CC) $(CFLAGS) -c $< -o $@

# Ejecutar con una expresión por defecto
run: $(TARGET)
	./$(TARGET) "sin(x)"

# Ejecutar con una expresión personalizada
# Uso: make run-expr EXPR="x^2 + 2*x + 1"
run-expr: $(TARGET)
	./$(TARGET) "$(EXPR)"

clean:
	rm -f $(TARGET) $(OBJ)
