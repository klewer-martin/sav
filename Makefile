CC := cc
CLIBS := `sdl2-config --libs --cflags`
CFLAGS := -lSDL2_image -lm -Wall -pedantic -ansi -std=c99
SRCS := sav.c util.c sort.c
OBJS := $(SRCS:.c=.o)

TARGET := sav

.PHONY: all clean

all: $(TARGET) clean

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(CLIBS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(CLIBS) -c $< -o $@

clean:
	rm -f $(OBJS)
