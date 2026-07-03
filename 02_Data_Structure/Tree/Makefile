TARGET = tree_test
OBJS = tree_test.o tree.o
CC = gcc	
CFLAGS = -c -Wall -g	
CPPFLAGS = -MMD -MP   # 生成依赖文件，并处理头文件变更

# 生成可执行文件:
$(TARGET): $(OBJS)
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# 自动包含所有生成的依赖文件（.d）
-include $(OBJS:.o=.d)

# 清理：删除可执行文件、所有 .o 和 .d 依赖文件
clean:
	rm -f $(TARGET) $(OBJS) $(OBJS:.o=.d)