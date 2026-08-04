Target := pipe_test msg_recv msg_send shm_test
CC := gcc

# 管道练习
pipe_test: pipe_test.c
	$(CC) $^ -o $@

# 消息队列练习
msg_recv: msg_recv.c
	$(CC) $^ -o $@
msg_send: msg_send.c
	$(CC) $^ -o $@

# 共享内存练习
shm_test: shm_test.c
	$(CC) $^ -o $@

clean:
	rm -f *.o $(Target)