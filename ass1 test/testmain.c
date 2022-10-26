#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<libgen.h>

int main(int argc, char* argv[]){
    int test = fork();
    if(test<0){printf("FAILED!");}
    if(test==0){
        char* argv[5] = {"gcc","-o","test.o","test.c",NULL};

        execv("gcc",argv);
        char* argv2[2] = {"./test.o",NULL};
        execv("./test.o",argv2);
    }else{
        wait(NULL);
    }
}