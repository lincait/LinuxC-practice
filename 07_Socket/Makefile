Target := client server
CC := gcc

server: server.c
	$(CC) $^ -o $@

client: client.c
	$(CC) $^ -o $@

clean:
	rm -f *.o $(Target)