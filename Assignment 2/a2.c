#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
char **getInput(){
    char *line = NULL;
    size_t length = 0;
    getline(&line,&length,stdin);
    printf("Your input of size %d, is %s",length/sizeof(char ),line);
    return NULL;
}
void shell_loop(){

}
int main(int argc, char* argv[]){
    shell_loop();
    getInput();
return 0;
}