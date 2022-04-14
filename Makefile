CC := cc
CLIBS := `sdl2-config --libs --cflags`
CFLAGS := -lSDL2_ttf -lm -Werror -pedantic -ansi -std=c99 -g -pthread
SRCS := main.c sav.c util.c sort.c drw.c sdl_extra.c array.c
OBJS := $(SRCS:.c=.o)
LIBS := array.h status.h

TARGET := sav

.PHONY: all clean

all: $(TARGET) clean

$(TARGET): $(OBJS) $(HEADERS) $(LIBS)
	$(CC) $(CLIBS) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CLIBS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
