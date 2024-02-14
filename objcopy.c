#include <elf.h>
#include <stdlib.h>
#include <string.h>
#include "bfd.h"
#include <fcntl.h>
#include <unistd.h>

void text_section(bfd *abfd){

    //Use the unbuffered io open syscall to open the text-output file to read and write
    int fd = open("text-output",O_RDWR);
    //Get the text section of the bfd data structure
    asection *section = bfd_get_section_by_name(abfd, ".text");
    //get the size of the text section
    bfd_size_type size = bfd_section_size(section);
    //allocate enough memory to store the contents of the text sections
    bfd_byte *contents = (bfd_byte*)malloc(size);
   
    //if contents are null, then we failed to allocate memory
    if (contents == NULL){
        bfd_perror("Failed to allocate memory\n");
        bfd_close(abfd);
        exit(EXIT_FAILURE);
    }
    //We use the bfd_get_section_contents to read the data from the text section reading
    //starting at offset 0 and given size bytes and reads it into contents in memory
    bfd_get_section_contents(abfd,section,contents,0,size);
    //Use the write system call and write the contents into the given file descriptor of the text-output binary file
    write(fd,contents,size);
    //free the memory of the contents stored after writing it to the file
    free(contents);
    //close the file descriptor
    close(fd); 
}