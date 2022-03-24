CC := cc
CLIBS :=
CFLAGS := `sdl2-config --libs --cflags` -lSDL2_image -lm
SRCS := sav.c util.c
OBJS := $(SRCS:.c=.o)

TARGET := sav

.PHONY: all clean

all: $(TARGET) clean

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
