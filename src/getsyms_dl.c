#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "bfd.h"
#include "objsym.h"

int main(int argc, char *argv[]){

  if (argc != 2){
    write(STDERR_FILENO,"No file argument\n",sizeof("No file argument\n"));
    exit(-1);
  }

  char *filename = argv[1];
  find_symbols(filename);
  exit(0);
}
