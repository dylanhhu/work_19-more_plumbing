all: ui.o worker.o
	gcc -o ui ui.o
	gcc -o worker worker.o

ui.o: ui.c
	gcc -c ui.c

worker.o: worker.c
	gcc -c worker.c

clean:
	rm *.o
	rm ui worker
