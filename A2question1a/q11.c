#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


int *p;
FILE* file;

void* countA(){
    struct  timespec ta2;
    struct sched_param *sp=(struct sched_param*)malloc(sizeof(struct sched_param));
    sp->sched_priority=p[0];
    pthread_setschedparam(pthread_self(),SCHED_OTHER,sp);
    clock_gettime(CLOCK_REALTIME,&ta2);
    nice(0);
    unsigned long long c = 0;
    for(long long i=0;i<__UINT32_MAX__;i++){
         c++;
    }
    struct timespec ta1;
    clock_gettime(CLOCK_REALTIME,&ta1);
    long long ans = ta1.tv_sec-ta2.tv_sec;
    ans +=(ta1.tv_nsec-ta2.tv_nsec)/1e9;
    fprintf(file,"countA =%f\n",ans);
    return NULL;
}

void* countB(){
    struct  timespec tb1,tb2;
    struct sched_param *sp=(struct sched_param*)malloc(sizeof(struct sched_param));
    sp->sched_priority=p[1];
    pthread_setschedparam(pthread_self(),SCHED_RR,sp);
    clock_gettime(CLOCK_REALTIME,&tb2);
    unsigned long long c = 0;
    for(long long i=0;i<__UINT32_MAX__;i++){
        c++;
    }
    clock_gettime(CLOCK_REALTIME,&tb1);
    long long ans = tb1.tv_sec-tb2.tv_sec;
    ans +=(tb1.tv_nsec-tb2.tv_nsec)/1e9;
    fprintf(file,"countB =%f\n",ans);
    return NULL;
}

void* countC(){
    struct  timespec tc1,tc2;
    struct sched_param *sp=(struct sched_param*)malloc(sizeof(struct sched_param));
    sp->sched_priority=p[2];
    pthread_setschedparam(pthread_self(),SCHED_FIFO,sp);
    clock_gettime(CLOCK_REALTIME,&tc2);
    unsigned long long c = 0;
    for(long long i=0;i<__UINT32_MAX__;i++){
        c++;
    }
    long long ans = tc1.tv_sec-tc2.tv_sec;
    ans +=(tc1.tv_nsec-tc2.tv_nsec)/1e9;
    clock_gettime(CLOCK_REALTIME,&tc1);
    fprintf(file,"countC =%f\n",ans);
    return NULL;
}


int main(){
    pthread_t A,B,C;
    p = (int *)malloc(sizeof(int)*3);
    p[0] = 0;
    p[1] = 1;
    p[2] = 1;
    file = fopen("output.txt","w");
        pthread_create(&A,NULL,&countA,NULL);
        pthread_create(&B,NULL,&countB,NULL);
        pthread_create(&C,NULL,&countC,NULL);
        pthread_join(A,NULL);
        pthread_join(B,NULL);
        pthread_join(C,NULL);
    free(p);
    fclose(file);
    return 0;
}