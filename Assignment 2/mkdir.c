#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<libgen.h>

int main(int argc, char* argv[]){
    char* path = strcat(argv[2],argv[1]);
    printf("Path = %s",path);
    return 0;
}