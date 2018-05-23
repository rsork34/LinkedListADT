run: list test
	gcc -Wall -std=c99 ADT.o listTest.o -o run

list:
	gcc -Wall -std=c99 -c sorkinRyanLab1.c -o ADT.o

test:
	gcc -Wall -std=c99 -c listTest.c -o listTest.o

clean:
	rm *.o
	rm run
