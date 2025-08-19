main:main.o functions.o
	gcc main.o functions.o -o main
main.o:main.c header.h
	gcc -c main.c
functions.o:functions.c header.h
	gcc -c functions.c
clean:
	rm -f *.o main
