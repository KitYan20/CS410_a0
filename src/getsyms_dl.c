#include <unistd.h>
#include <stdlib.h>
#include "bfd.h"
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
    write(STDERR_FILENO,"No file argument or RTLD (Run Time Dynamic Linker) option\n",sizeof("No file argument or RTLD (Run Time Dynamic Linker) option\n"));
    exit(-1);
  }
  
  
  int rtld_flag = atoi(argv[2]);
  
  if (rtld_flag == 1){
    RDTSC(start);
    handle = dlopen("./libobjdata.so",RTLD_LAZY);
    RDTSC(finish);
  }else if (rtld_flag == 2){
    RDTSC(start);
    handle = dlopen("./libobjdata.so",RTLD_NOW);
    RDTSC(finish);
  }else{
    write(STDERR_FILENO,"Wrong RTLD (Run Time Dynamic Linker) option\n",sizeof("Wrong RTLD (Run Time Dynamic Linker) option\n"));
    exit(-1);
  }
  //To caluculate the time of a CPU frequency in seconds, you do
  // seconds = 1/frequency(Mhz) * 10 ^ 6
  double frequency = 2304 * (1e6);
  char buffer[20];
  double time = (finish - start)/frequency;
  //Convert seconds to microseconds
  time = time * 1e6;
  itoa(time,buffer);
  write(1,buffer,sizeof(buffer));
  write(1,"\n",sizeof("\n"));
  func = dlsym(handle,"find_symbols");
  func(filename);
  
  dlclose(handle);
  
  exit(0);
}
