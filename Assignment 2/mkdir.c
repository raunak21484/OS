#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<libgen.h>
#include<sys/stat.h>
int main(int argc, char* argv[]){
    char* path = strcat(argv[2], "/");
    char* pathfinal = strcat(path,argv[1]);
    printf("path = %s\n",pathfinal);
    int t= mkdir(pathfinal,0777);
    printf("t= %d",t);
    return t;
}