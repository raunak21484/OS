#include<stdio.h>
#include<stdlib.h>
void NULLIFY2D(char** array){
    int ptr = 0;
    while(array[ptr]!=NULL){
        free(arr[ptr]);
        ptr++;
    }
    free(array);
}
int main(){
    int x= 5, y = 10;
    int *p = &x;
    printf("p is %p",&p);
    int *p = &y;
    char ** chararray = (char**)malloc(3*sizeof(char*));
    chararray[0] = (char*)malloc(3*sizeof(char));
    chararray[0][0]= 'a';
    chararray[0][1]= 'b';
    chararray[0][2]= '\0';
    chararray[1] = (char*)malloc(3*sizeof(char));
    chararray[1][0]= 'b';
    chararray[1][1]= 'c';
    chararray[1][2]= '\0';
    chararray[2] = NULL;
    printf("%d",(chararray==NULL));
    if(chararray!=NULL){
        printf("\n %d %d\n",(chararray[0]==NULL),(chararray[1]==NULL));
    }
    NULLIFY2D(chararray);
    printf("%d",(chararray==NULL));
    if(chararray!=NULL){
        printf("\n %d %d\n",(chararray[0]==NULL),(chararray[1]==NULL));
    }
    return 0;
}