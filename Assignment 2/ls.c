#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<libgen.h>
#include <dirent.h>

int main(int argc, char* argv[]){//path, "XX"->"-a and -m flag", "total path", NULL
    printf("%s\n%s\n%s\n",argv[0],argv[1],argv[2]);
    return 0;
}