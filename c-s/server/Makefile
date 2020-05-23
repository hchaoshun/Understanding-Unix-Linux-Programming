serv: serv.o socklib.o
	cc serv.o socklib.o -o serv

serv.o: serv.c socklib.h
	cc -c serv.c -o serv.o

socklib.o: socklib.c socklib.h
	cc -c socklib.c -o socklib.o

clean:
	rm *.o
