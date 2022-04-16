CC := gcc
CLIBS := `sdl2-config --libs` -lSDL2_ttf -lm
CFLAGS := `sdl2-config --cflags` -Wall -Wshadow -pedantic -ansi -std=c99 -pthread
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

TARGET := sav

.PHONY: all clean

all: $(TARGET) clean

$(TARGET): $(OBJS) $(HEADERS)
	$(CC) $(CLIBS) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CLIBS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
