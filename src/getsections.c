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
  print_sections(filename);
  
  return 0;
}
