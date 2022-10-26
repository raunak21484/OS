#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<libgen.h>
char * _PROGRAM_DIRECTORY;
char ** getSplittedLine(char* line, char* delim){
    int cap = 16;
    int len = 0;
    char **tokens = malloc(sizeof(char*) *cap );
    char *tokentemp = strtok(line, delim);

    while (tokentemp!=NULL) {
        tokens[len++] = tokentemp;
        if (len >= cap) {
            cap*=(int)1.75;
            tokens = realloc(tokens, cap * sizeof(char*));
        }
        tokentemp = strtok(NULL, delim);
    }
    tokens[len] = NULL;

    return tokens;
}
char **getInput(){
    char *line = NULL;
    size_t l = 0;
    getline(&line,&l,stdin);
    if(line[0]=='\n' && line[1]=='\0'){return NULL;}
    return getSplittedLine(line," ");
}
void echo(char** segment){
    int ptr =1;
    int EOL = 1;
    if(segment[1] != NULL){
        if(strcmp(segment[1],"-n")==0 || strcmp(segment[1],"-n\n")==0){
            EOL = 0;
            ptr = 2;
        }else if(strcmp(segment[1],"-E")==0 || strcmp(segment[1],"-E\n")==0){
            ptr = 2;
        }
    }
    int marking = -1, dollarmarking = -1;
    while(segment[ptr]!=NULL){
        int ptr2 = 0;
        marking = -1;dollarmarking=-1;
        while(segment[ptr][ptr2]!='\0'){
            if(segment[ptr][ptr2]=='\\'){
                if(segment[ptr][ptr2+1]=='\\' && marking!= ptr2){
                    marking = ptr2+1;
                    printf("%c",'\\');}
                ptr2++;
                continue;
            }
            if(segment[ptr][ptr2]=='$'){
                if(segment[ptr][ptr2+1]=='$' && dollarmarking!=ptr2){
                    dollarmarking = ptr2+1;
                    printf("%d",(int)getpid());
                }
                ptr2++;
                continue;
            }
            if(segment[ptr+1]==NULL && segment[ptr][ptr2]=='\n' && EOL==0){
                ptr2++;
            }
            printf("%c",segment[ptr][ptr2]);
            ptr2++;
        }
        ptr++;
        if(segment[ptr]!=NULL){printf(" ");}
    }
}
char* echoMessage(char** segment, int ptr){
    int EOL = 1;
    char * ECHOMESSAGE = (char*)malloc(15000 * sizeof(char));
    int eptr = 0;
    int marking = -1, dollarmarking = -1;
    while(segment[ptr]!=NULL){
        int ptr2 = 0;
        marking = -1;dollarmarking=-1;
        while(segment[ptr][ptr2]!='\0'){
            if(segment[ptr][ptr2]=='\\'){
                if(segment[ptr][ptr2+1]=='\\' && marking!= ptr2){
                    marking = ptr2+1;
                    //printf("%c",'\\');
                    ECHOMESSAGE[eptr] = '\\';
                    eptr++;
                }
                ptr2++;
                continue;
            }
            if(segment[ptr][ptr2]=='$'){
                ECHOMESSAGE[eptr] = '$';
                eptr++;
                if(segment[ptr][ptr2+1]=='$' && dollarmarking!=ptr2){
                    dollarmarking = ptr2+1;
                    //printf("%d",(int)getpid());
                }
                ptr2++;
                continue;
            }
            if(segment[ptr+1]==NULL && segment[ptr][ptr2]=='\n' && EOL==0){
                ptr2++;
            }
            //printf("%c",segment[ptr][ptr2]);
            ptr2++;
            ECHOMESSAGE[eptr] = segment[ptr][ptr2];
            eptr++;
        }
        ptr++;
        if(segment[ptr]!=NULL){ECHOMESSAGE[eptr] = ' '; eptr++;}
    }
    ECHOMESSAGE[eptr] = '\0';
    return ECHOMESSAGE;
}
char* delim(char* input){
    char *input2 = strtok(input,"\n");
    return input2;
}
void changeDir(char ** segment){
    int c =0,ptr1 =1;
    int tptr = 0;
    while(segment[ptr1]!=NULL){
        tptr = 0;
        while(segment[ptr1][tptr]!='\0'){
            c++;
            tptr++;
        }
        ptr1++;
        c++;
    }
    if(ptr1==1 || (strcmp(segment[1],"\n")==0)){
        chdir("/home");
        return;
    }
    printf("segment[1] is '%s'\n",segment[1]);
    char* newDir = (char*)malloc((c+1)*sizeof(char));
    newDir[c] = '\0';
    ptr1 = 1;
    c=0;
    while(segment[ptr1]!=0){
        tptr = 0;
        while(segment[ptr1][tptr]!='\0'){
            newDir[c] = segment[ptr1][tptr];
            c++;
            tptr++;
        }
        ptr1++;
        newDir[c] = ' ';
        c++;
    }
    char * temp = delim(newDir);
    //printf("Temp = %s\n",temp);
    int fin = chdir(temp);
    if(fin!=0){
        printf("Could not find directory: %s\n",temp);
    }
    free(temp);

}
char* getPWD(){
    char* buffer = NULL;
    size_t size = 0;
    return getcwd(buffer,size);
}
char* delimslash(char * input){
    return strtok(input,"/");
}
void call_mkdir(char* path){
    pid_t proc = fork();
    if (proc < 0) {
        printf("Failed!\n");
        return;
    }
    if (proc == 0) {


    } else {
        wait(NULL);
    }
}
//char* mergeSegment(char ** segment, char mergeChar, int ptr){]
//    if(segment[ptr]==NULL){
//        return NULL;
//    }
//    int c=0,ptr1=ptr,tptr=0;
//    while(segment[ptr1]!=NULL){
//        tptr= 0;
//        while(segment[ptr1][tptr]!=NULL){
//            tptr++;
//            c++;
//        }
//        c++
//        ptr1++;
//    }
//    char* mergedSeg = (char*)malloc((c+1)*sizeof(char));
//    c = 0,ptr1 = ptr;
//    while(segment[ptr1]!=NULL){
//        tptr = 0;
//        while(segment[ptr1][tptr]!=NULL){
//            mergedSeg[c] = segment[ptr1][tptr];
//            tptr++;
//            c++;
//        }
//        mergedSeg[c] = mergeChar;
//        c++;
//        ptr1++;
//    }
//    mergedSeg[c] = '\0';
//
//}
void mkdir1(char ** segment){
    if(segment[1]!=NULL) {
        if(strcmp(segment[1],"\n")==0 || strcmp(segment[1]," ") == 0){return;}
        else if(strcmp(segment[1],"-v")==0){
            char* message = echoMessage(segment,2);
            printf("echo message = %s\n",message);
            //MERGE EVERYTHING AFTER 1
            //char * path = getPWD();
            //MAKE DIRECTORY NORMALLY + PRINT MESSAGE

        }else if(strcmp(segment[1],"-v\n")==0 || strcmp(segment[1],"-p\n")==0){
            printf("mkdir: Missing operand\n");
        }else if(strcmp(segment[1],"-p")){

        }else{
            //MAKE DIRECTORY NORMALLY
        }

    }
}
void shell_loop(){
    while(1) {
        char * x = getPWD();
        printf("\033[0;31m<\033[0;36m%s\033[0;31m>\033[0m ",basename(x));
        free(x);
        char **segment = getInput();
        if(segment == NULL){continue;}
        int ptr = 0;
        char* s0 = delim(segment[0]);
        //char* s0 = segment[0];
        if (segment[0]==NULL) {}
        else if (strcmp(s0, "exit") == 0) {free(s0); break; }
        else if(strcmp(s0,"cd")==0){ changeDir(segment);}
        else if(strcmp(s0,"pwd")==0){
            char * cwd = getPWD(segment);
            printf("%s\n",cwd);
            free(cwd);
        }
        else if(strcmp(s0,"echo")==0){ echo(segment);}
        else if(strcmp(s0,"mkdir")==0){mkdir1(segment);}
        else{printf("Segment[0] is %s!\n",segment[0]);printf("Command Not Found!\n");}
        free(s0);

    }
}
int main(int argc, char* argv[]){
    _PROGRAM_DIRECTORY = getPWD();
    shell_loop();
//    char ** segment = getInput();
//    int ptr = 0;
//    while(segment[ptr]!=NULL){
//        printf("%s\n",segment[ptr]);
//        ptr++;
//    }
return 0;
}