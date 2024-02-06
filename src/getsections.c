#include <unistd.h>
#include <stdlib.h>
#include "bfd.h"
#include "objsect.h"
#include "objcopy.h"


int main(int argc, char *argv[]){
  //Error checking to ask for user to input a file argument to get the sections
  if (argc != 2){
    write(STDERR_FILENO,"No file argument\n",sizeof("No file argument\n"));
    exit(EXIT_FAILURE);
  }
  //Get the file from the first argument using a char pointer
  const char *filename = argv[1];
  
  //This is where we use the BFD library and bfd_init() must be called first to access all the functions in the library
  bfd_init();

  //Open the the target file with a pointer to an instance of a BFD structure
  bfd *abfd = bfd_openr(filename,"elf64-x86-64" /*elf32-i386*/);
  
  //Must check for format of the object
  if (!bfd_check_format(abfd,bfd_object)){
    //Print back an error to the terminal
    bfd_perror("Error opening the file");
    //Close the bfd library ending all operations
    bfd_close(abfd);
    //exit the program with a failure
    exit(EXIT_FAILURE);
  }else{
    //Call the bfd_map_over_sections to iterate through each section of the gile argument
    //find_sections function will be called to print out each of the section contents for the map_over_sections function
    bfd_map_over_sections(abfd,find_sections,NULL);
    //text_section will get the contents of the .text section in either ELF binary file or object file
    text_section(abfd);
    //Close the bfd library ending all operations
    bfd_close(abfd);
    
  }
  //Exit the program with no error
  exit(EXIT_SUCCESS);
}
