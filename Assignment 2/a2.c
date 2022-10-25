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

    char *delim = " \t\r\n";
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
void shell_loop(){
    while(1) {
        printf("$ ");
        char **segment = getInput();
        int ptr = 0;

        if (segment[0]==NULL) {continue;}
        else if (strcmp(segment[0], "exit") == 0) { break; }
        else if(strcmp(segment[0],"cd")==0){}
        else if(strcmp(segment[0],"pwd")==0){}
        else{printf("Command Not Found!\n");continue;}
    }
}
int main(int argc, char* argv[]){
    shell_loop();

return 0;
}