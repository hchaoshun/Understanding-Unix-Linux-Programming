dgrecv: dgrecv.o dgramlib.o
	cc dgrecv.o dgramlib.o -o dgrecv

dgrecv.o: dgrecv.c dgramlib.h
	cc -c dgrecv.c -o dgrecv.o

dgramlib.o: dgramlib.c dgramlib.h
	cc -c dgramlib.c -o dgramlib.o

clean:
	rm -f *.o 
