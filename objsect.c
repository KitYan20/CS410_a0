#include "objsect.h"
#include "bfd.h"
#include <unistd.h>
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
  //Create a character array of char data types for 9 bytes for the hex string
  char hexString[9];
  //Create a character array of char data types for 256 bytes for the section name
  char newString[256];

  //Create a copy of the section name
  strncpy(newString,name,sizeof(newString)-1);
  //set the section names last value null
  newString[sizeof(newString)-1] = '\0';
  //Write the string back into standard out
  write(1,&newString,sizeof(newString));
  write(1," ",sizeof(""));
  //Convert primitive data types of long to hex string and do the same process
  //of writing string back to standard output
  numbers_to_ASCII((long)size,hexString);
  write(1,&hexString,sizeof(hexString));
  write(1," ",sizeof(""));
  numbers_to_ASCII((long)vma,hexString);
  write(1,&hexString,sizeof(hexString));
  write(1," ",sizeof(""));
  numbers_to_ASCII((long)file_pos,hexString);
  write(1,&hexString,sizeof(hexString));
  write(STDOUT_FILENO,"\n",sizeof("\n"));
}
