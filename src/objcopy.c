#include <stdio.h>
#include <elf.h>
#include <stdlib.h>
#include <string.h>
#include "bfd.h"

void text_section(bfd *abfd){

    FILE* output = fopen("text-output","wb");
    asection *section = bfd_get_section_by_name(abfd, ".text");
    bfd_size_type size = bfd_section_size(section);
    bfd_byte *contents = (bfd_byte*)malloc(size);
   
    
    if (contents == NULL){
        //printf("Failed to allocate memory\n");
        bfd_close(abfd);
        exit(-1);
    }

    bfd_get_section_contents(abfd,section,contents,0,size);

    fwrite(contents,sizeof(bfd_byte),size,output);
    free(contents);
    fclose(output);
  
    
}