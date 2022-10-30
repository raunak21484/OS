#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<libgen.h>

char* slashTreatment(char* str){
    char* newstr = (char*)malloc((strlen(str)+1)*sizeof(char));
    int ptr =0;
    for(int i=0;str[i]!='\0';i++){
        if(str[i]!='\\'){
            newstr[ptr]= str[i];
            ptr++;
            continue;
        }
        if(str[i+1]!='\0'){
            newstr[ptr] = str[i+1];
            i++;
            ptr++;
        }
    }
    if(newstr[ptr-1]=='\n'){newstr[ptr-1]='\0';}
    newstr[ptr] = '\0';
    return newstr;
}
char * concatString(char * string1, char * string2){

    int c1 = (string1!=NULL?strlen(string1):0);
    int c2 = (string2!=NULL?strlen(string2):0);
    int c = c1+c2;
    //printf("c = %d\n",c);
    char* stringfinal = (char*)malloc(sizeof(char)*(c+1));

    for(int i=0;i< c1;i++){
        stringfinal[i] = string1[i];
    }

    for(int i=0;i< c2;i++){
        stringfinal[i+ c1] = string2[i];
    }
    stringfinal[c] = '\0';
    //printf("here");
    //printf("stringfinal = %s\n",stringfinal);
    return stringfinal;
}
int main(int argc, char* argv[]){//mkname, flags(T,N), pwd, list of all names, NULL
    printf("In cat.c, program: \n");
    for(int i=0;argv[i]!=NULL;i++){
        printf("'%s'\n",argv[i]);
    }
    printf("DONE \n\n");
    int tflag=0;
    char* tempstr = NULL;
    FILE* fptr;
    char bufch;
    for(int i=3;argv[i]!=NULL;i++){
        tflag =0;
        if(argv[i][strlen(argv[i])-1]=='\\'){
            int c=1;
            while(strlen(argv[i])-1-c>=0 && argv[i][strlen(argv[i])-1-c]=='\\'){
                c++;
            }
            if(c%2==1 && argv[i+1]!=NULL){
                tflag = 1;
            }
        }
        if(tflag ==1){
            argv[i+1] = concatString(argv[i],concatString(" ",argv[i+1]));
        }else{
            tempstr = argv[i];
        }

        if(tempstr!=NULL){
            char* t2 = slashTreatment(tempstr);
            char * strfinal = concatString(argv[2],t2);
            printf("PWD: %s\n",argv[2]);
            printf("Final String: '%s'\n",strfinal);
            fptr = fopen(strfinal,"r");
            if(fptr==NULL){
                printf("Unable to open file '%s'\n",strfinal);
                tempstr = NULL;
                break;
            }
            int lc =0;
            while((bufch = fgetc(fptr))!=EOF){

                if(bufch!='\\'){
                    printf("%c",bufch);
                }
                else{
                    if((bufch = fgetc(fptr))!=EOF) {
                        if (argv[1][0] == '0' || bufch !='t') {
                            printf("\\%c",bufch);
                        }
                        else { printf("^I"); }
                    }else{
                        printf("\\");
                    }
                }
                if(bufch == '\n'){
                    lc++;
                    if(argv[1][1]=='1'){
                        printf("%6d   ",lc);
                    }
                }
            }

            fclose(fptr);
            tempstr = NULL;
        }
    }
    return 0;
}