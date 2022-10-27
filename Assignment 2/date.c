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
    char* bigarrayM[13] = {"January","February","March","April","May","June","July","August","September","October","November","December",NULL};
    char* smallarrayM[13] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sept","Oct","Nov","Dec",NULL};
    char* bigArrayD[8] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday",NULL};
    char* smallArrayD[8] = {"Sun","Mon","Tue","Wed","Thur","Fri","Sat",NULL};
    if(strcmp(argv[1],"default")==0){
        printf("%s %d %s %d %d:%d:%d %s UTC",bigArrayD[currtime.tm_wday],currtime.tm_mday,bigarrayM[currtime.tm_mon],(currtime.tm_year+1900),((currtime.tm_hour>=12?currtime.tm_hour-12:currtime.tm_hour)),currtime.tm_min,currtime.tm_sec,((currtime.tm_hour>=12?"PM":"AM")));
        return 0;
    }
    return 0;
}