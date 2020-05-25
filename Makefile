CC=g++
CFLAGS=-c -Wall -O2 -std=c++14
LFLAGS=
PROGS= server
OBJS= server.o digraph.o dijkstra.o 

# executable targets
all: server

server: server.o digraph.o dijkstra.o
	$(CC) server.o digraph.o dijkstra.o -o server $(LFLAGS)

# object targets
server.o: server.cpp digraph.h wdigraph.h dijkstra.h
	$(CC) server.cpp -o server.o $(CFLAGS)

digraph.o: digraph.cpp digraph.h
	$(CC) digraph.cpp -o digraph.o $(CFLAGS)

dijkstra.o: dijkstra.h dijkstra.cpp heap.h
	$(CC) dijkstra.cpp -o dijkstra.o $(CFLAGS)

clean:
	@rm $(OBJS) $(PROGS)