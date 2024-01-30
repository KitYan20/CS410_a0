//#include <config.h>
#include <unistd.h>
#include <stdio.h>
#include "bfd.h"
#include "objsect.h"
int main(int argc, char *argv[]){

  if (argc != 2){
    fprintf(stderr, "Usage: %s <object_file>\n",argv[1]);
    return 1;
  }

  const char *filename = argv[1];
  //print_sections(filename);
  bfd_init();
  bfd *abfd = bfd_openr(filename,NULL);
  
  if (!bfd_check_format(abfd,bfd_object)){
    bfd_perror("Error opening the file");
    return 1;
  }else{
    unsigned int n;
    n = bfd_count_sections(abfd);
    printf("Num sections = %d\n", n);
    asection *p;
    for (p = abfd->sections; p != NULL;p = p->next){
      printf("Section Name %s\n",p->name);
      printf("VMA 0x%lx\n",(unsigned long)p->vma);
      printf("Size 0x%lx\n",(long)p->size);
      printf("File Position %ld\n",(long)p->filepos);
     
    }
    bfd_close(abfd);
  }
  return 0;
}
