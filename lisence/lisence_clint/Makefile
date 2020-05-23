lclint: lclint.o dgramlib.o lclint_func.o
	cc lclint.o dgramlib.o lclint_func.o -o lclint

dgramlib.o: dgramlib.c dgramlib.h
	cc -c dgramlib.c  -o dgramlib.o

lclint_func.o: lclint_func.c lclint_func.h dgramlib.h
	cc -c lclint_func.c -o lclint_func.o 

clean:
	rm -f *.o
