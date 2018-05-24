run: list test
	gcc -Wall -g -std=c99 ADT.o -Iinclude listTest.o -o run

list:
	gcc -Wall -g -std=c99 -c -Iinclude src/sorkinRyanLab1.c -o ADT.o

test:
	gcc -Wall -g -std=c99 -c -Iinclude src/listTest.c -o listTest.o

clean:
	rm *.o
	rm run
