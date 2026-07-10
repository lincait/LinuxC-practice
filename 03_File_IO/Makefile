Target := mycopy
CC := gcc
CFLAGS := -c -Wall -g -MMD

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
DEPS := $(SRCS:.c=.d)

$(Target): $(OBJS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $< $(CFLAGS) -o $@

-include $(DEPS)

clean:
	rm -f *.o *.d $(Target)