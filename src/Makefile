CC=gcc
CFLAGS= -c
HEAD= socks.h
OBJ = client.o server.o main.o

all: compile

compile: $(OBJ)
	$(CC) $(OBJ) -o Program

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf *.o Program