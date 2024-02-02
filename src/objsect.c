#include "objsect.h"
#include "bfd.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "helper.h"

void find_sections(bfd *abfd, asection *p, PTR obj){
  //Set a buffer size of 1024 bytes
  char buffer[1024];
  //Type cast a char pointer in order to get the address of the name section
  char* name = (char*)p->name;
  //type cast a unsigned long pointer to get the memory adress of the vma section
  long* vma= (long*)p->vma;
  //type cast a long pointer to get the memory address of the size section
  long* size= (long*)p->size;
  //type cast a long point to get the memory address of the file position section
  long* file_pos= (long*)p->filepos;
  int n;
  char hexString[17];
  char newString[256];
  //snprintf will help store the entire series of characters and numerical values into a character array buffer
  //n will print back out the total size of the buffer array in order to write back to standard out
  n = snprintf(buffer,sizeof(buffer),
		 "Section Name: %-25s Size: 0x%-18lx VMA: 0x%-25lx  File Position: 0x%-10lx\n",
		 name,(long)size,(long)vma,(long)file_pos);
  write(1,&buffer,n);

  // strncpy(newString,name,sizeof(newString)-1);
  // newString[sizeof(newString)-1] = '\0';
  // write(1,&newString,sizeof(newString));
  // write(1," ",sizeof(""));
  // numbers_to_ASCII((long)size,hexString);
  // write(1,&hexString,sizeof(hexString));
  // write(1," ",sizeof(""));
  // numbers_to_ASCII((long)vma,hexString);
  // write(1,&hexString,sizeof(hexString));
  // write(1," ",sizeof(""));
  // numbers_to_ASCII((long)file_pos,hexString);
  // write(1,&hexString,sizeof(hexString));
  // write(STDOUT_FILENO,"\n",sizeof("\n"));
}
