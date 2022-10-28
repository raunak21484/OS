#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<libgen.h>

// get ECHO TO WORK! $'\n'

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
char* echoMessage(char** segment, int ptr, char sep){
    int EOL = 0;
    int tsize =0;
    int tptr = ptr;
    while(segment[tptr]!=NULL){tsize+=strlen(segment[tptr]);tptr++;}
//    printf("TSIZE: %d\n",tsize);
    char * ECHOMESSAGE = (char*)malloc((tsize*2) * sizeof(char));
    int eptr = 0;
    int marking = -1, dollarmarking = -1;

    while(segment[ptr]!=NULL){
        //printf("Segment[%d] = %s\n",ptr,segment[ptr]);
        int ptr2 = 0;
        marking = -1;dollarmarking=-1;
        while(segment[ptr][ptr2]!='\0'){

            if(segment[ptr][ptr2]=='\\'){
                //printf("FOUND1!!");
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
                //printf("FOUND2!");
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
                //printf("HERE");
                ptr2++;
            }
            //printf("%c",segment[ptr][ptr2]);
            ECHOMESSAGE[eptr] = segment[ptr][ptr2];
            ptr2++;

            eptr++;
        }
        ptr++;
        if(segment[ptr]!=NULL){ECHOMESSAGE[eptr] = sep; eptr++;}
    }
    ECHOMESSAGE[eptr] = '\0';
    //printf("EPTR = %d",eptr);
//    printf("\nMessage: \n");
//    for(int i=0;i<eptr;i++){
//        printf("'%c' ",ECHOMESSAGE[i]);
//    }
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
int call_mkdir(char* path){
    pid_t proc = fork();
    if (proc < 0) {
        printf("Failed!\n");
        return 2;
    }
    if (proc == 0) {
        char* mkname = strcat(_PROGRAM_DIRECTORY,"/mkdir.o");
        char* pwd = getPWD();
        char* arr[4] = {mkname,path,pwd,NULL};
        printf("PATH = %s\n",path);
        char * env[1] = {NULL};

        execve(mkname,arr,env);
        return 3;

    } else {
        int status;
        wait(&status);
        return status;
    }
}
void date(char ** segment){
    int fid = fork();
    if(fid<0){printf("Failed due to unexpected error1!\n");return;}
    if(fid==0){
        char* mkname = strcat(_PROGRAM_DIRECTORY,"/date.o");
        if(segment[1]==NULL || strcmp(segment[1],"-u")==0 || strcmp(segment[1],"--utc")==0 || strcmp(segment[1],"--universal")==0 ||
                                    strcmp(segment[1],"-u\n")==0 || strcmp(segment[1],"--utc\n")==0 || strcmp(segment[1],"--universal\n")==0||strcmp(segment[1],"\n")==0){
            //segment[0][strlen(segment[0])-1] = '\0';
            printf("in HEREEE!!");
            char* argv[3]=  {mkname,"default",NULL};
            char* env[1] = {NULL};
            printf("mkname = %s\n",mkname);
            execve(mkname,argv,env);
        }else if(strcmp(segment[1],"-R")==0 || strcmp(segment[1],"--rfc-email")==0  || strcmp(segment[1],"-R\n")==0 || strcmp(segment[1],"--rfc-email\n")==0){
                printf("in here!!!");
            char *argv[3] = {mkname,"r",NULL};
                char* env[1] = {NULL};
                execve(mkname,argv,env);
            }
        char * temp = echoMessage(segment,0,'|');
        printf("seg: %s\n",temp);
        printf("Failed due to unexpected error2!\n");
        return;
    }else{
        int status;
        wait(&status);
        if(status!=0){printf("Failed due to unexpected error3!\n");}
    }
}
void mkdir1(char ** segment){
    if(segment[1]!=NULL) {
        if(strcmp(segment[1],"\n")==0 || strcmp(segment[1]," ") == 0){return;}
        else if(strcmp(segment[1],"-v")==0){
            char* message = echoMessage(segment,2,' ');
            int stat =call_mkdir(message);
            //printf("\nstat = %d\n",stat);//
            if(stat==0){
                printf("Created Directory: %s\n",message);
            }else{
                printf("Creation of directory failed!\n");
            }

        }else if(strcmp(segment[1],"-v\n")==0 || strcmp(segment[1],"-p\n")==0){
            printf("mkdir: Missing operand\n");
        }else if(strcmp(segment[1],"-p")==0){
            char* message = echoMessage(segment,2,' ');
            char** segmentTWO = getSplittedLine(message,"/");
            int c =0;
            for(int i=0;segmentTWO[i]!=NULL;i++){
                c+=strlen(segmentTWO[i]);
            }
            char * temp = (char*)malloc(sizeof(char)*(2*c+1));
            int ptr = 0;
            for(int i=0;segmentTWO[i]!=NULL;i++){
                printf("%s\n",segmentTWO[i]);
                for(int j=0;j<strlen(segmentTWO[i]);j++){
                    temp[ptr] = segmentTWO[i][j];
                    ptr++;
                }
                temp[ptr] = '/';
                ptr++;
                temp[ptr+1] = '\0';
                //strncat(temp,segmentTWO[i],strlen(segmentTWO[i]));
                if(call_mkdir(temp)!=0){
                    printf("ERROR, temp = %\n",temp);
                }
            }
            free(temp);
        }else{
            printf("DEFAULT");
            char* message = echoMessage(segment,1,' ');
            if(call_mkdir(message)!=0){ printf("Creation of directory failed!\n");}
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
            char * cwd = getPWD();
            printf("%s\n",cwd);
            free(cwd);
        }
        else if(strcmp(s0,"echo")==0){ echo(segment);}
        else if(strcmp(s0,"mkdir")==0){mkdir1(segment);}
        else if(strcmp(s0,"date")==0){date(segment);}
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