# Makefile for CS371 Programming Assignment
# Cohen Archbold  University of Kentucky

# Compile Client
client: client.c 
	gcc -Wall client.c -o client 

# Compile server
server: server.c
	gcc -Wall server.c -o server 

# Compile Client and Server
all: server.c client.c
	gcc -Wall server.c -o server 
	gcc -Wall client.c -o client 

# Remove files
clean:
	rm -f client
	rm -f server
	rm -f rec.txt