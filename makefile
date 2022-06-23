# CC=arm-linux-gnuabi-gcc
CC=gcc
CCFLAGS=
INCLUDES=
LFLAGS=-L/usr/lib/x86_64-linux-gnu
LIBS=-lcurl -lpthread

SRC=requestor.c
OBJ=$(SRC:.c=.o)
MAIN=test

RM=rm -rf

.c.o:
	$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

$(MAIN): $(OBJ)
	$(CC) $(CCFLAGS) $(INCLUDES) -o $(MAIN) $(OBJ) $(LFLAGS) $(LIBS)

all: $(MAIN)

clean:
	$(RM) $(MAIN) *.o *~
