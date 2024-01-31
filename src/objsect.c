#include "objsect.h"
#include "bfd.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
void find_sections(bfd *abfd, asection *p, PTR obj){
  //Set a buffer size of 1024 bytes
  char buffer[1024];
  //Type cast a char pointer in order to get the address of the name section
  char* name = (char*)p->name;
  //type cast a unsigned long pointer to get the memory adress of the vma section
  unsigned long* vma= (unsigned long*)p->vma;
  //type cast a long pointer to get the memory address of the size section
  long* size= (long*)p->size;
  //type cast a long point to get the memory address of the file position section
  long* file_pos= (long*)p->filepos;
  int n;
  //snprintf will help store the entire series of characters and numerical values into a character array buffer
  //n will print back out the total size of the buffer array in order to write back to standard out
  n = snprintf(buffer,sizeof(buffer),
		 "Section Name: %-25s VMA: 0x%-18lx Size: 0x%-25lx  File Position: 0x%-70lx\n",
		 name,(long)vma,(long)size,(long)file_pos);
  write(1,&buffer,n);
}
