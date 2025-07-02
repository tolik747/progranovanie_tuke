CC=gcc
CFLAGS=-std=c11 -Wall -Werror
LDLIBS=#-lm
ps4=ps4

all: $(ps4)

$(ps4): bmp.o main.o transformations.o
# cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) bmp.o main.o transformations.o $(LDLIBS) -o $(ps4)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

bmp.o: bmp.c bmp.h
	$(CC) $(CFLAGS) -c bmp.c -o bmp.o

transformations.o: transformations.c transformations.h
	$(CC) $(CFLAGS) -c transformations.c -o transformations.o

clean:
	rm -rf $(ps4) *.o
