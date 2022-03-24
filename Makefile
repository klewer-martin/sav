CC := gcc
CLIBS :=
CFLAGS := `sdl2-config --libs --cflags` -lSDL2_image -lm
SRCS := "sav.c util.c"
OBJS := $(SRCS:.c=.o)

TARGET := sav

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS)
