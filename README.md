### General Info
Running on a Ubuntu Linux Virtual Machine using Virtual Box. Also, the function to get the text in objcopy.c will be called in
getsections.c and getsections_dl.c
### CPU Configuration
CPU: Intel Core i7-11800-H runing aorund 2300 mhz.
### Compiling the programs
Compiling the programs is fairly simple as I created a Makefile to compile/link all the neccesary dependencies (eg static libraries, shared libraries) into it's corresponding binary files.
The only thing that you have to do first is to set where the shared object library will be available in the computer. Write the following command above in the terminal to set the library path

```bash
LD_LIBRARY_PATH=./
```
```bash
export LD_LIBRARY_PATH
```
After that, you can compile all the required programs running the following command on your terminal:
```bash
make all
```
After running this command, it should compile all the c files into object files and link it to create the corresponding binary ELF files getsections, getsyms, getsections_dl, getsyms_dl. 
I've also created some shell script as well to better automate the process for Task B to calculate the average latency. It will test getsections_dl, getsyms_dl with RTLD_LAZY and RTLD_NOW. 
It will also take a object file or ELF file as an argument. I've created an example "test" binary file to run for each binary.
You can test the shell script with the command above:
```bash
./stats_script test
```

