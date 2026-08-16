Target := Thread_lab
CC := gcc
CFLAGS := -c -g -Wall -MMD -pthread $(shell pkg-config --cflags glib-2.0)
LIBS := -pthread $(shell pkg-config --libs glib-2.0)

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
DEPS := $(SRCS:.c=.d)

$(Target): $(OBJS)
	$(CC) $^ -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

-include $(DEPS)

clean:
	rm -f *.o *.d $(Target)
