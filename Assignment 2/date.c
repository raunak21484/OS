#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<libgen.h>
#include<sys/stat.h>
#include<time.h>

int main(int argc, char* argv[]){
    time_t time = time(NULL);
    struct tm currtime =(*localtime(&time));
    char* bigarray[12] = {"January","February","March","April","May","June","July","August","September","October",""};
    if((strcmp(argv[1]),"default")==0){
        printf("")
    }
    return 0;
}