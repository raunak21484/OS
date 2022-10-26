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
        execv("./test.c",NULL);
        printf("MAA");
    }else{
        wait(NULL);
    }
}