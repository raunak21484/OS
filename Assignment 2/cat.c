#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<libgen.h>

int main(int argc, char* argv[]){
    printf("In cat.c, program: \n");
    for(int i=0;argv[i]!=NULL;i++){
        printf("'%s'\n",argv[i]);
    }
    return 0;
}