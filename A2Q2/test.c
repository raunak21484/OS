#define _GNU_SOURCE
#include<unistd.h>
#include<sys/syscall.h>
#include<stdio.h>
#include<stdlib.h>

#define SYS_kern_2D_memcpy 451;

int main(){
float matrix1[4][5] = {{1.0,2.0,3.0,4.0,5.0},{6.0,7.0,8.0,9.0,10.0},{11.0,12.0,13.0,14.0,15.0},{16.0,17.0,18.0,19.0,20.0}};
float matrix2[4][5];
    printf("Original matrix: \n");
    for(int i=0;i<4;i++){
        for(int j=0;j<5;j++){
            printf("%lf ",matrix1[i][j]);
        }
        printf("\n");
    }
    printf("Now calling syscall!\n");
    int answer  = syscall(SYS_kern_2D_memcpy,matrix1,matrix2);
    if(answer<0){
        printf("Error!");
        exit(1);
    }
    printf("matrix2 after copying: \n");
    for(int i=0;i<4;i++){
        for(int j=0;j<5;j++){
            printf("%lf ",matrix2[i][j]);
        }
        printf("\n");
    }

    return 0;
}