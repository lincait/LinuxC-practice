Target := Proc_monitor
CC := gcc
CFLAGS := -c -g -Wall -MMD

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