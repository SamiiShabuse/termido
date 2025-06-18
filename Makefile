CC = gcc
CFLAGS = -Wall -Wextra -I./src
OBJ = build/main.o build/todo.o 
TARGET = termido

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
