all : server client run

server: server.c
	gcc server.c -o server

client: client.c
	gcc client.c -o client

run : server
	./server

