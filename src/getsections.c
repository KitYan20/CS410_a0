#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "bfd.h"
#include "objsect.h"

int main(int argc, char *argv[]){

  if (argc != 2){
    printf("No File");
    exit(-1);
  }

  const char *filename = argv[1];
  bfd_init();
  bfd *abfd = bfd_openr(filename,"elf64-x86-64" /*elf32-i386*/);
  
  if (!bfd_check_format(abfd,bfd_object)){
    bfd_perror("Error opening the file");
    bfd_close(abfd);
    exit(-1);
  }else{
    
    bfd_map_over_sections(abfd,find_sections,NULL);
    bfd_close(abfd);
  }
  exit(0);
}
