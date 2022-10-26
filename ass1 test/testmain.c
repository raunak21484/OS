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
        char *argv2[2] = {"./test.o", NULL};
        char *env[1] = {NULL};
        execve("./test.o", argv2,env);
        printf("FORK 1 FAILED!");
        }
    else{
        wait(NULL);
    }
}