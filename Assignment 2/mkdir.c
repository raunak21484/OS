#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<libgen.h>
#include<sys/stat.h>
int main(int argc, char* argv[]){
    char* path = strcat(argv[2], strcat("/",argv[1]));
    return mkdir(path);
}