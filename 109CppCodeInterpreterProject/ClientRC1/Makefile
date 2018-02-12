OBJS = client.o TCPSocket.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=c++14 $(DEBUG)
LFLAGS = -Wall $(DEBUG)

# client
client_misvm : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o client_misvm

# objects

client.o : client.cpp TCPSocket.h TCPSocket.cpp
	$(CC) $(CFLAGS) client.cpp

TCPSocket.o : includes.h common.h TCPSocket.h TCPSocket.cpp
	$(CC) $(CFLAGS) TCPSocket.cpp

clean:
	\rm *.o client_misvm
