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
    while(segment[ptr]!=NULL){
        int ptr2 = 0;
        while(segment[ptr][ptr2]!='\0'){
            if(segment[ptr][ptr2]=='\\'){
                ptr2++;
                continue;
            }
            printf("%c",segment[ptr][ptr2]);
            ptr2++;
        }
        ptr++;
        if(segment[ptr]!=NULL){printf(" ");}
    }
}
void stripEnd(char* string){
    int c = 0;
    while(string[c]!='\0'){
        c++;
    }
    string[c-1] = '\0';
    string
}
void shell_loop(){
    while(1) {
        printf("$ ");
        char **segment = getInput();
        int ptr = 0;

        if (segment[0]==NULL) {continue;}
        else if (strcmp(segment[0], "exit") == 0 || strcmp(segment[0], "exit\n") == 0) { break; }
        else if(strcmp(segment[0],"cd")==0 || strcmp(segment[0],"cd\n")==0){}
        else if(strcmp(segment[0],"pwd")==0|| strcmp(segment[0],"pwd\n")==0){printf("hiii");}
        else if(strcmp(segment[0],"echo")==0 || strcmp(segment[0],"echo\n")==0){ echo(segment);}
        else{printf("Segment[0] is %s!\n",segment[0]);printf("Command Not Found!\n");continue;}
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