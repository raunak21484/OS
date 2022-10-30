#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<libgen.h>

int main(int argc, char* argv[]){
    printf("File to delete: '%s'\n",argv[1]);
    return remove(argv[1]);
}