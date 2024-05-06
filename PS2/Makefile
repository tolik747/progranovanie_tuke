CFLAGS = -std=c11 -Werror -Wall -Wconversion -lm
OUTPUT = ps2

all: $(OUTPUT)

$(OUTPUT): main.o hof.o k.o ui.o
	gcc $(CFLAGS) main.o hof.o k.o ui.o -lm -o $(OUTPUT)

main.o: main.c
	gcc $(CFLAGS) -c main.c -o main.o

hof.o: hof.c hof.h
	gcc $(CFLAGS) -c hof.c -o hof.o

k.o: k.c k.h
	gcc $(CFLAGS) -c k.c -o k.o

ui.o: ui.c ui.h
	gcc $(CFLAGS) -c ui.c -o ui.o

clean:
	rm -rf *.o $(OUTPUT)
