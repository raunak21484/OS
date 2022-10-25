#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
char **getInput(){
    char *line = NULL;
    size_t l = 0;
    getline(&line,&l,stdin);
    int cap = 16;
    int len = 0;
    char **tokens = malloc(sizeof(char*) *cap );
    char *tokentemp = strtok(line, " ");

    while (tokentemp!=NULL) {
        tokens[len++] = tokentemp;
        if (len >= cap) {
            cap*=(int)1.75;
            tokens = realloc(tokens, cap * sizeof(char*));
        }
        tokentemp = strtok(NULL, " ");
    }
    tokens[len] = NULL;

    return tokens;
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
    int marking = -1;
    while(segment[ptr]!=NULL){
        int ptr2 = 0;
        marking = -1;
        while(segment[ptr][ptr2]!='\0'){
            if(segment[ptr][ptr2]=='\\'){
                if(segment[ptr][ptr2+1]=='\\' && marking!= ptr2){
                    marking = ptr2+1;
                    printf("%c",'\\');}
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
char* delim(char* input){
    char *input2 = strtok(input,"\n");
    return input2;
}

char* getPWD(){
    char* buffer = NULL;
    size_t size = 0;
    return getcwd(buffer,size);
}
void shell_loop(){
    while(1) {
        printf("$ ");
        char **segment = getInput();
        int ptr = 0;
        char* s0 = delim(segment[0]);
        //char* s0 = segment[0];
        if (segment[0]==NULL) {}
        else if (strcmp(s0, "exit") == 0) {free(s0); break; }
        else if(strcmp(s0,"cd")==0){}
        else if(strcmp(s0,"pwd")==0){
            char * cwd = getPWD();
            printf("%s\n",cwd);
            free(cwd);
        }
        else if(strcmp(s0,"echo")==0){ echo(segment);}
        else{printf("Segment[0] is %s!\n",segment[0]);printf("Command Not Found!\n");}
        free(s0);

    }
}
int main(int argc, char* argv[]){
    shell_loop();
//    char ** segment = getInput();
//    int ptr = 0;
//    while(segment[ptr]!=NULL){
//        printf("%s\n",segment[ptr]);
//        ptr++;
//    }
return 0;
}