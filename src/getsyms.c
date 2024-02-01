#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "bfd.h"
#include "objsym.h"

int main(int argc, char *argv[]){

  if (argc != 2){
    printf("No File");
    exit(-1);
  }

  char *filename = argv[1];
  find_symbols(filename);
  exit(0);
}
