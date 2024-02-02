CC = gcc
PROGS = getsections getsyms
SLIBS = libobjdata.a

all: $(PROGS) $(SLIBS)

getsections: getsections.o libobjdata.a
	$(CC) getsections.o libobjdata.a -lbfd -o getsections
getsections.o:./src/getsections.c
	$(CC) -c  ./src/getsections.c -I ./include
getsyms: getsyms.o libobjdata.a
	$(CC) getsyms.o libobjdata.a -lbfd -o getsyms
getsyms.o: ./src/getsyms.c
	$(CC) -c ./src/getsyms.c -I ./include
helper.o: ./src/helper.c
	$(CC) -c ./src/helper.c -I ./include
getsections_dl.o: ./src/getsections_dl.c
	$(CC) -fPIC -c ./src/getsections_dl.c -I ./include
getsyms_dl.o: ./src/getsyms_dl.c
	$(CC) -fPIC-c ./src/getsyms_dl.c -I ./include

objsect.o: ./src/objsect.c
	$(CC) -c ./src/objsect.c -I ./include
objsym.o: ./src/objsym.c
	$(CC) -c ./src/objsym.c -I ./include
libobjdata.a: objsect.o objsym.o helper.o
	ar rcs libobjdata.a objsect.o objsym.o helper.o

clean:
	rm -f $(PROGS) *.o *.a
