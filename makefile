compile: server.o client.o
	gcc -o servers server.o
	gcc -o clients client.o

server.o: server.c
	gcc -c server.c
client.o: client.c
	gcc -c client.c


client: clients
	./clients
server: servers
	./servers
	
	
clean:
	rm *.o
	rm servers
	rm clients
