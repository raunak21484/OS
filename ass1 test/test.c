#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<libgen.h>
int main()
{
    char* test = "1234";
    char* bi;
    strcpy(bi,test);
    printf("bi: %s\n",bi);
    bi[0] = '2';
    printf("bi: %s\ntest: %s\n",bi,test);
    return 0;
}