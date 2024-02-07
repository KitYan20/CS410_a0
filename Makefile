CC = gcc
PROGS = getsections getsyms getsections_dl getsyms_dl test
SLIBS = libobjdata.a libobjdata.so

all: $(PROGS) $(SLIBS)
test:test.o
	ld -g test.o -o test
test.o:test.s
	as -g test.s -o test.o
getsections: getsections.o libobjdata.a
	$(CC) getsections.o libobjdata.a -lbfd -o getsections
getsections.o:./src/getsections.c
	$(CC) -c  ./src/getsections.c -I ./include

getsyms: getsyms.o libobjdata.a
	$(CC) getsyms.o libobjdata.a -lbfd -o getsyms
getsyms.o: ./src/getsyms.c
	$(CC) -c ./src/getsyms.c -I ./include

helper.o: ./src/helper.c
	$(CC) -fPIC -c ./src/helper.c -I ./include
objsect.o: ./src/objsect.c
	$(CC) -fPIC -c ./src/objsect.c -I ./include
objsym.o: ./src/objsym.c
	$(CC) -fPIC -c ./src/objsym.c -I ./include
objcopy.o: ./src/objcopy.c
	$(CC) -fPIC -c ./src/objcopy.c -I ./include

helpera.o: ./src/helper.c
	$(CC) -c ./src/helper.c -I ./include -o helpera.o
objsecta.o: ./src/objsect.c
	$(CC) -c  ./src/objsect.c -I ./include -o objsecta.o
objsyma.o: ./src/objsym.c
	$(CC) -c ./src/objsym.c -I ./include -o objsyma.o
objcopya.o: ./src/objcopy.c
	$(CC) -c ./src/objcopy.c -I ./include -o objcopya.o

getsections_dl.o: ./src/getsections_dl.c
	$(CC) -c ./src/getsections_dl.c -I ./include
getsyms_dl.o: ./src/getsyms_dl.c
	$(CC) -c ./src/getsyms_dl.c -I ./include

getsections_dl: getsections_dl.o 
	$(CC) getsections_dl.o -L. libobjdata.so -lbfd -ldl -o getsections_dl

getsyms_dl: getsyms_dl.o 
	$(CC) getsyms_dl.o -L. libobjdata.so -lbfd -ldl -o getsyms_dl


libobjdata.so: objsect.o objsym.o objcopy.o helper.o
	$(CC) -shared -o libobjdata.so objsect.o objsym.o objcopy.o helper.o


libobjdata.a: objsecta.o objsyma.o helpera.o objcopya.o
	ar rcs libobjdata.a objsecta.o objsyma.o helpera.o objcopya.o

clean:
	rm -f $(PROGS) *.o *.a *.so 
