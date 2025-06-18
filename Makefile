CC = gcc
CFLAGS = -Wall -Wextra -I./src
OBJ = src/main.o src/todo.o
TARGET = termido

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
