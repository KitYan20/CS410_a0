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
  void (*func)(bfd *abfd,asection *sec, PTR obj);
  void (*func2)(bfd *abfd);

  if (argc != 2){
    write(STDERR_FILENO,"No file argument\n",sizeof("No file argument\n"));
    exit(-1);
  }
  unsigned long long start,finish;
  const char *filename = argv[1];
  bfd_init();
  bfd *abfd = bfd_openr(filename,"elf64-x86-64" /*elf32-i386*/);
  
  if (!bfd_check_format(abfd,bfd_object)){
    bfd_perror("Error opening the file");
    bfd_close(abfd);
    exit(-1);
  }else{
    RDTSC(start);
    handle = dlopen("./libobjdata.so",RTLD_LAZY);
    RDTSC(finish);

    //Finds the address of the symbol for the find_sections function in the dynamic library
    func = dlsym(handle,"find_sections");
    //Use that function for bfd_map_over_sections instead of calling it from the header file
    bfd_map_over_sections(abfd,func,NULL);
    
    //To caluculate the time of a CPU frequency in seconds, you do
    // seconds = 1/frequency(Mhz) * 10 ^ 6
    double frequency = 2304 * (1e6);
    char buffer[20];
    double time = (finish - start)/frequency;
    //Convert seconds to microseconds
    time = time * 1e6;
    itoa(time,buffer);
    write(1,buffer,sizeof(buffer));
    
    
    
  }
  exit(0);
}
