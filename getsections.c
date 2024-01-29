#include "bfd.h"
#include <unistd.h>

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
    return;
  }
  asection *p;
  for (p = abdfd->sections; p!= NULL, p->next){
    
  }
}
