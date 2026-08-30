CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic
TARGET = stands_app
SRC = src/main.c src/stand.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
