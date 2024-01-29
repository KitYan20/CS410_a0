CC = gcc

getsections: getsections.o libobjdata.a
	$(CC) getsections.o libobjdata.a -lbfd -o getsections
getsections.o:./src/getsections.c
	$(CC) -c  ./src/getsections.c -I ./include
objsect.o: ./src/objsect.c
	$(CC) -c ./src/objsect.c -I ./include
libobjdata.a: objsect.o  
	ar rcs libobjdata.a objsect.o 
clean:
	rm -f getsections *.o *.a
