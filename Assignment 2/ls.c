#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<libgen.h>
#include <dirent.h>

int main(int argc, char* argv[]){//path, "XX"->"-a and -m flag", "total path", NULL
    //printf("%s\n%s\n%s\n",argv[0],argv[1],argv[2]);
    DIR *directory;
    directory = opendir(argv[2]);
    struct dirent *filetemp, *filetemp2;
    int dispdot = (argv[1][0]-'0');
    int sepcomma = argv[1][1] - '0';
    int i=0;
    if(directory!=NULL){
        filetemp = readdir(directory);
        filetemp2 = readdir(directory);
        while(filetemp!=NULL){

            if(filetemp->d_name[0]=='.'){
                if(dispdot){
                    i++;
                if(i%2){printf("\033[0;33m%s\033[0m",filetemp->d_name);}
                else{printf("\033[0;32mm%s\033[0m",filetemp->d_name);}
                if(sepcomma&& filetemp2!=NULL){printf(",");}
                printf(" ");
                }
            }else{
                i++;
                if(i%2){printf("\033[0;33m%s\033[0m",filetemp->d_name);}
                else{printf("\033[0;32mm%s\033[0m",filetemp->d_name);}
                    if(sepcomma&& filetemp2!=NULL){printf(",");}
                    printf(" ");
            }
            filetemp = filetemp2;
            filetemp2 = readdir(directory);
        }
    }else{
        return 1;
    }
    printf("\n");
    return 0;
}