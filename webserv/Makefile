webserv: webserv.o socklib.o
	cc webserv.o socklib.o -o webserv

webserv.o: webserv.c socklib.h
	cc -c webserv.c -o webserv.o

socklib.o: socklib.c socklib.h
	cc -c socklib.c -o socklib.o

clean:
	rm -r *.o
