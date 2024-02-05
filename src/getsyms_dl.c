#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "bfd.h"
#include "objsym.h"
#include <dlfcn.h>
#include "helper.h"
#define RDTSC(var)                                              \
  {                                                             \
    uint32_t var##_lo, var##_hi;                                \
    asm volatile("lfence\n\trdtsc" : "=a"(var##_lo), "=d"(var##_hi));     \
    var = var##_hi;                                             \
    var <<= 32;                                                 \
    var |= var##_lo;                                            \
  }
int main(int argc, char *argv[]){
  void *handle;
  void (*func)(char *filename);
  unsigned long long start,finish;
  char *filename = argv[1];
  
  if (argc != 3){
    write(STDERR_FILENO,"No file argument\n",sizeof("No file argument\n"));
    exit(-1);
  }
  // if (argv[2] != 1 || (int)argv[2] != 2){
  //   write(STDERR_FILENO,"Need RTLD Lazy or RTLD Now\n",28);
  //   exit(-1);
  // }
  
  
  int rtld_flag = atoi(argv[2]);
  if (rtld_flag == RTLD_LAZY){
    RDTSC(start);
    handle = dlopen("./libobjdata.so",RTLD_LAZY);
    RDTSC(finish);
  }else{
    RDTSC(start);
    handle = dlopen("./libobjdata.so",RTLD_NOW);
    RDTSC(finish);
  }
  long long frequency = 2304.000;
  char buffer[20];
  unsigned long long time = (finish - start)/frequency;
  itoa(time,buffer);
  write(1,buffer,sizeof(buffer));
  write(1,"\n",sizeof("\n"));
  func = dlsym(handle,"find_symbols");
  func(filename);
  
  dlclose(handle);
  
  exit(0);
}
