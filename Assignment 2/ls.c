#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<libgen.h>
#include <dirent.h>

int main(int argc, char* argv[]){//path, "XX"->"-a and -m flag", "total path", NULL
    printf("%s\n%s\n%s\n",argv[0],argv[1],argv[2]);
    char[5] sep;
    if(argv[1][1] == '1'){
        sep = ", ";
    }else{
        sep = " ";
    }
    DIR *directory;
    directory = opendir(argv[2]);
    struct dirent *dir;
    int dispdot = (int)(argv[1][0]-'0');

    return 0;
}