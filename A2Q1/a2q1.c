#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>



void func1(){
    struct timespec timespecs[2];
    int S1 = clock_gettime(CLOCK_REALTIME, &(timespecs[0]));
    pid_t pid1 = fork();
    struct sched_param schedparam1;
    schedparam1.sched_priority=0;
    int waitid1;
    sched_setscheduler(pid1,SCHED_OTHER,&schedparam1);
    if (pid1 == 0){
        execlp("/bin/sh","sh","bash1.sh",NULL);
    }
    else if (pid1 > 0){
        waitid1 = waitpid(pid1,0,0);
        int E1=clock_gettime(CLOCK_REALTIME,&(timespecs[1]));
        double ans=(timespecs[1].tv_sec-timespecs[0].tv_sec);
        ans+=(timespecs[1].tv_nsec-timespecs[0].tv_nsec)/(double)1e9;
        FILE *outputfile=fopen("Outputfile.txt","a");
        fprintf(outputfile,"1: %lf\n",ans);
        fclose(outputfile);
    }
}

void func2(){
    struct timespec timespecs[2];
    int S1 = clock_gettime(CLOCK_REALTIME, &(timespecs[0])));
    pid_t pid2 = fork();
    struct sched_param schedparam2;
    schedparam2.sched_priority=1;
    int waitid2;
    sched_setscheduler(pid2, SCHED_FIFO, &schedparam2);
    if (pid2 == 0){
        execlp("/bin/sh","sh","bash2.sh",NULL);
    }
    else if(pid2 > 0){
        waitid2 = waitpid(pid2,0,0);
        int E1=clock_gettime(CLOCK_REALTIME,&(timespecs[1]));
        double ans=(timespecs[1].tv_sec-timespecs[0].tv_sec);
        ans+=(timespecs[1].tv_nsec-timespecs[0].tv_nsec)/(double)1e9;
        FILE *outputfile=fopen("Outputfile.txt","a");
        fprintf(outputfile,"2: %lf\n",ans);
        fclose(outputfile);
    }
}

void func3(){
    struct timespec timespecs[2];
    int S1 = clock_gettime(CLOCK_REALTIME, &(timespecs[0]));
    pid_t pid3 = fork();
    struct sched_param schedparam3;
    schedparam3.sched_priority=0;
    int waitid3;
    sched_setscheduler(pid3,SCHED_RR,&schedparam3);
    if (pid3 == 0){
        execlp("/bin/sh","sh","bash3.sh",NULL);
    }
    else if(pid3 > 0){
        waitid3 = waitpid(pid3,0,0);
        int E1=clock_gettime(CLOCK_REALTIME,&(timespecs[1]));
        double ans=(timespecs[1].tv_sec-timespecs[0].tv_sec);
        ans+=(timespecs[1].tv_nsec-timespecs[0].tv_nsec)/(double)1e9;
        FILE *outputfile=fopen("Outputfile.txt","a");
        fprintf(outputfile,"3: %lf\n",ans);
        fclose(outputfile);
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
                wait(NULL);
            }
        }else{
            wait(NULL);
        }
    }else{
        wait(NULL);
    }
}