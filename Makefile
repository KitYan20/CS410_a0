CC = gcc
PROGS = getsections getsyms getsections_dl getsyms_dl test
SLIBS = libobjdata.a 
LIBS = libobjdata.so
OBJS = objsect.o objsym.o objcopy.o helper.o
SOBJS = objsecta.o objsyma.o helpera.o objcopya.o
LDLIBS = -lbfd -ldl
LD = -L.

all:  $(LIBS) $(PROGS) $(SLIBS) 
%.o:%.c
	$(CC) -fPIC -c $< -o $@
%a.o:%.c
	$(CC) -c $< -o $@
libobjdata.so: $(OBJS)
	$(CC) -shared -o $@ $^
libobjdata.a: $(SOBJS)
	ar rcs $@ $^

test:test.o
	ld -g $^ -o $@
test.o:test.s
	as -g $^ -o $@
getsections: getsections.o $(SLIBS)
	$(CC) $^ -lbfd -o $@
getsyms: getsyms.o $(SLIBS)
	$(CC)  $^ -lbfd -o $@
getsections_dl: getsections_dl.o $(LIBS)
	$(CC)  $(LD) $^ $(LDLIBS) -o $@

getsyms_dl: getsyms_dl.o $(LIBS)
	$(CC) $(LD) $^ $(LDLIBS) -o $@
clean:
	rm -f $(PROGS) *.o *.a *.so 
