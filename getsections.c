#include "config.h"
#include <unistd.h>
#include <stdio.h>
#include "bfd.h"
int main(int argc, char *argv[]){

  if (argc != 2){
    fprintf(stderr, "Usage: %s <object_file>\n",argv[1]);
    return 1;
  }
  //Needs to call this function before calling any other BFD function to initialize all the internal data structures
  bfd_init();

  bfd *abfd = bfd_openr(argv[1], NULL);

  if (!abfd){
    bfd_perror("Error opening the file");
    return 1;
  }
  //Print the column headers
  int n;
  char buffer[1024];
  asection *p;
  n = snprintf(buffer, sizeof(buffer),
	       "%-25s %-20s %-20s %-20s\n",
	       "Section Name", "VMA", "Size", "File Position");
  write(1,buffer,n);
  for (p = abfd->sections; p!= NULL, p->next){
    n = snprintf(buffer,sizeof(buffer),
		 "%-25s %-181x %-20ld %20ld\n",
		 p->name, (unsigned long)p->vma, (long)p->cooked_size, (long)p->filepos);
    write(1,buffer,n);
  }
  bfd_close(abfd);
  return 0;
}
