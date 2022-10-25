#include<stdio.h>
#include<stdlib.h>

int main(){
    int *p = (int*)malloc(sizeof(int)*100);
    printf("location of p: %p",p);
    free(p);
    int *p = (int*)malloc(sizeof(int)*100);
    printf("location of p: %p",p);
    int *p = (int*)malloc(sizeof(int)*100);
    printf("location of p: %p",p);
    return 0;
}