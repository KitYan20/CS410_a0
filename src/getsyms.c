#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "bfd.h"
#include "objsym.h"

int main(int argc, char *argv[]){
  //Error checking for an argument file input
  if (argc != 2){
    write(STDERR_FILENO,"No file argument\n",sizeof("No file argument\n"));
    exit(EXIT_FAILURE);
  }
  //Get the file via a character pointer
  char* filename = argv[1];
  //Call our find_symbols function in objsym
  find_symbols(filename);
  //Exit the program with success
  exit(EXIT_SUCCESS);
}
