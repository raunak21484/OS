#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>



void fcaller1(){
    struct timespec s1,e1;
    int S1 = clock_gettime(CLOCK_REALTIME, &s1);
    pid_t pid1 = fork();
    struct sched_param schedp1;
    schedp1.sched_priority=0;
    sched_setscheduler(pid1,SCHED_OTHER,&schedp1);
    if (pid1 == 0){
        execlp("/bin/sh","sh","bash1.sh",NULL);
        // sleep(10);
    }
    else if (pid1 > 0){
        int waitid1 = waitpid(pid1,0,0);
        int E1=clock_gettime(CLOCK_REALTIME,&e1);
        double ans=(e1.tv_sec-s1.tv_sec+(e1.tv_nsec-s1.tv_nsec)/(double)1e9);
        ;
        printf("----------RunTime for first thread: %lfs----------\n",(ans));
    }
}

void fcaller2(){
    struct timespec s1,e1;
    int S1 = clock_gettime(CLOCK_REALTIME, &s1);
    pid_t pid2 = fork();
    struct sched_param schedp2;
    schedp2.sched_priority=1;
    sched_setscheduler(pid2, SCHED_FIFO, &schedp2);
    if (pid2 == 0){
        execlp("/bin/sh","sh","bash2.sh",NULL);
        // sleep(10);
    }
    else if(pid2 > 0){
        int waitid1 = waitpid(pid2,0,0);
        int E1=clock_gettime(CLOCK_REALTIME,&e1);
        double ans=(e1.tv_sec-s1.tv_sec+(e1.tv_nsec-s1.tv_nsec)/(double)1e9);
        ans/=(double)1e9;
        printf("----------RunTime for second thread: %lfs----------\n",(ans));
    }
}

void fcaller3(){
    struct timespec s1,e1;
    int S1 = clock_gettime(CLOCK_REALTIME, &s1);
    pid_t pid3 = fork();
    struct sched_param schedp3;
    schedp3.sched_priority=0;
    sched_setscheduler(pid3,SCHED_RR,&schedp3);
    if (pid3 == 0){
        execlp("/bin/sh","sh","bash3.sh",NULL);
        // sleep(10);
    }
    else if(pid3 > 0){
        int waitid1 = waitpid(pid3,0,0);
        int E1=clock_gettime(CLOCK_REALTIME,&e1);
        double ans=(e1.tv_sec-s1.tv_sec+(e1.tv_nsec-s1.tv_nsec)/(double)1e9);
        ans/=(double)1e9;
        printf("----------RunTime for third thread: %lfs----------\n",(ans));
    }
}


int main(){
    pid_t pid1, pid2, pid3;

    pid1 = fork();
    if(pid1<0){
        printf("Error pid1!\n");
        return 1;
    }
    if(pid1==0){
        fcaller1();
        pid2 = fork();
        if(pid2<0){
            printf("Error pid2!\n");
            return 1;
        }
        if(pid2 ==0){
            fcaller2();
            pid3 = fork();
            if(pid3<0){
                printf("Error pid3!\n");
                return 1;
            }
            if(pid3==0){
                fcaller3();
            }else{
                waitpid(pid3,0,0);
            }
        }else{
            waitpid(pid2,0,0);
        }
    }else{
        waitpid(pid1,0,0);
    }

}