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
    printf("$ ");
    char** segment = getInput();
    int ptr =0;
    if(strcmp(segment[0],"exit")!=0){shell_loop();}
}
int main(int argc, char* argv[]){
    shell_loop();

return 0;
}