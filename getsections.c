//#include <config.h>
#include <unistd.h>
#include <stdio.h>
#include "bfd.h"
extern void printsections(const char *filename);
int main(int argc, char *argv[]){

  if (argc != 2){
    fprintf(stderr, "Usage: %s <object_file>\n",argv[1]);
    return 1;
  }
  const char *filename = argv[1];
  printsections(filename);
  
  return 0;
}
