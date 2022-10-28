#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<libgen.h>
char * concatString(char * string1, char * string2){
    int c1 = strlen(string1);
    int c2 = strlen(string2);
    int c = c1+c2;
    printf("c = %d",c);
    char* stringfinal = (char*)malloc(sizeof(char)*(c+1));

    for(int i=0;i< c1;i++){
        stringfinal[i] = string1[i];
    }

    for(int i=0;i< c2;i++){
        stringfinal[i+ c1] = string2[i];
    }
    stringfinal[c] = '\0';
    printf("here");
    //printf("stringfinal = %s",stringfinal);
    return stringfinal;
}
int main()
{
    char* test = "1234";
    char* bi;
    strcpy(bi,test);
   char * third = concatString(test,bi);
  // printf("third = %s\n",third);
    return 0;
}