//#include <config.h>
#include "bfd.h"
#include <unistd.h>
#include <stdio.h>
void printsections(const char *file){
  
  //Needs to call this function before calling any other BFD function to initialize all the internal data structures
  bfd_init();
  //Opens the object file
  bfd *abfd = bfd_openr(file, NULL);

  if (!abfd){
    bfd_perror("Error opening the file");
  }
  //Print the column headers
  int n;
  char buffer[1024];
  asection *p;
  n = snprintf(buffer, sizeof(buffer),
	       "%-25s %-20s %-20s %-20s\n",
	       "Section Name", "VMA", "Size", "File Position");
  write(1,buffer,n);
  for (p = abfd->sections; p!= NULL; p->next){
    n = snprintf(buffer,sizeof(buffer),
		 "%-25s %-18lx %-20ld  %-20ld\n",
		 p->name, (unsigned long)p->vma, (long)p->size, (long)p->filepos);
    write(1,buffer,n);
  }
  bfd_close(abfd);
  
}
