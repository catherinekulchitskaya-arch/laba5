CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = postal_system
SOURCES = post.c postrussia.c
HEADERS = postrussia.h
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)


$(TARGET): $(OBJECTS)
 $(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c $(HEADERS)
 $(CC) $(CFLAGS) -c $< -o $@


clean:
 rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
 ./$(TARGET)


debug: $(TARGET)
 gdb ./$(TARGET)

valgrind: $(TARGET)
 valgrind --leak-check=full ./$(TARGET)

format:
 clang-format -i $(SOURCES) $(HEADERS)

.PHONY: all clean run debug valgrind format
