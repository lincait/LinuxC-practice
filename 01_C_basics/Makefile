CC = gcc
CFLAGS = -Wall
LDLIBS = -lm

# 匹配任意 .c 文件，生成同名可执行文件
%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -f $(basename $(wildcard *.c))