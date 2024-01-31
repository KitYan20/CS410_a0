#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "bfd.h"
#include "objsect.h"

int main(int argc, char *argv[]){

  if (argc != 2){
    fprintf(stderr, "Usage: %s <object_file>\n",argv[1]);
    exit(-1);
  }

  const char *filename = argv[1];
  bfd_init();
  bfd *abfd = bfd_openr(filename,NULL);
  
  if (!bfd_check_format(abfd,bfd_object)){
    bfd_perror("Error opening the file");
    exit(-1);
  }else{
    
    bfd_map_over_sections(abfd,find_sections,NULL);
    bfd_close(abfd);
  }
  exit(0);
}
