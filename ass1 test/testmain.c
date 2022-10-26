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
        int fork2= fork();
        if(fork2<0){printf("FORK FAILED!");}
        else if(fork2==0){
        char* argv[5] = {"gcc","-o","test.o","test.c",NULL};
        execv("gcc",argv);

        printf("FORK 2 FAILED!");
        }
        else {
            wait(NULL);
            char *argv2[2] = {"./test.o", NULL};
            execv("./test.o", argv2);
            printf("FORK 1 FAILED!");
        }
    }else{
        wait(NULL);
    }
}