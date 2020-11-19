client: client.c 
	gcc -o client client.c 

server: server.c
	gcc -o server server.c

all: server.c client.c
	gcc -o server server.c
	gcc -o client client.c

clean:
	rm client
	rm server
	rm rec.txt