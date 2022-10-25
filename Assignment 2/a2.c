#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
char **getInput(){
    char *line = NULL;
    size_t length = 0;
    getline(&line,&length,stdin);
    //printf("Your input of size %d, is %s",length,line);
    int c= 0;
    while(line[c]!='\0'){
        if(line[c]=='\n'||line[c]==' '|| line[c] == '\t'){
            c++;
        }
    }
    printf("C = %d",c);
//    int *sizes =  (int*)malloc(sizeof(int )*c);
//    for(int i=0;i<c;i++){
//        sizes[i] =0 ;
//    }
//    int ptr = 0,sp=0;
//    while(line[ptr]!='\0'){
//        if(line[ptr]=='\n' || line[ptr]==' ' || line[ptr] == '\t'){
//            sp++;
//            ptr++;
//            continue;
//        }
//        sizes[sp]++;
//        ptr++;
//
//    }
//    char** segment = (char**) malloc(sizeof(char*)*(c+1));
//    for(int i=0;i<c;i++){
//        segment[i] = (char*)malloc(sizeof(char) * sizes[i]);
//    }
//    ptr = 0;
//    for(int i=0;i<c;i++){
//        for(int j=0;j<sizes[i];j++){
//            segment[i][j] = line[ptr];
//            ptr++;
//        }
//    }
//    segment[c+1] = (char*)malloc(sizeof(char*));
//    segment[c+1][0] = '\0';
//    return segment;
    return NULL;
}
void shell_loop(){

}
int main(int argc, char* argv[]){
    shell_loop();
    char** segment = getInput();
    printf("hi");
//    int ptr =0;
//    while(segment[ptr][0]!='0'){
//        printf("%s\n",segment[ptr]);
//        ptr++;
//    }
return 0;
}