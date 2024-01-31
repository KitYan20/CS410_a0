//#include <config.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "bfd.h"
#include "objsect.h"
void find_sections(bfd *abfd, asection *p, PTR obj){
  printf("Section Name %s\n",p->name);
  printf("VMA 0x%lx\n",(unsigned long)p->vma);
  printf("Size 0x%lx\n",(long)p->size);
  printf("File Position %ld\n",(long)p->filepos);
}
int main(int argc, char *argv[]){

  if (argc != 2){
    fprintf(stderr, "Usage: %s <object_file>\n",argv[1]);
    exit(-1);
  }

  const char *filename = argv[1];
  //print_sections(filename);
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
