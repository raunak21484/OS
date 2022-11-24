#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sched.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
    pid_t p1,p2,p3;
    struct timespec s1,s2,s3,e1,e2,e3;
     struct sched_param* p1 = (struct sched_param*)malloc(sizeof(struct sched_param));
    if(p1!=NULL) p1->sched_priority=0;

    struct sched_param* p2 = (struct sched_param*)malloc(sizeof(struct sched_param));
    if(p2!=NULL) p2->sched_priority=1;

    struct sched_param* p3 = (struct sched_param*)malloc(sizeof(struct sched_param));
    if(p3!=NULL) p3->sched_priority=1;

    int S1 = clock_gettime(CLOCK_REALTIME, &s1);
    int S2 = clock_gettime(CLOCK_REALTIME, &s2);
    int S3 = clock_gettime(CLOCK_REALTIME, &s3);
    pid1 =  fork(); pid2 = fork(); pid3 = fork();
    if(!pid1){
        sched_setscheduler(pid1,SCHED_OTHER,p1);
        execlp("/bin/bash","sh","bash1.sh",NULL);
    }
    
    else if(!pid2){
        sched_setscheduler(pid2,SCHED_RR,p2);
        execlp("/bin/bash","sh","bash2.sh",NULL);
    }
    else if(!pid3){
        sched_setscheduler(pid3,SCHED_FIFO,p3);
        execlp("/bin/bash","sh","bash3.sh",NULL);
    }
    double fans1,fans2,fans3;
    for(int i =0; i<3; i++){
        pid_t pz = wait(NULL);
        printf("Released!\n");
        if(pz == pid1){
            int E1=clock_gettime(CLOCK_REALTIME,&e1);
            double ans1=e1.tv_sec-s1.tv_sec+e1.tv_nsec-s1.tv_nsec;
            //FILE *fp = fopen("readings.txt");
            fans1 = ans1;
            printf("RunTime for first thread: %lfs\n",(ans1));
            
        }
        else if(pz == pid2){
            int E2=clock_gettime(CLOCK_REALTIME,&e2);
            double ans2=e1.tv_sec-s1.tv_sec+e1.tv_nsec-s1.tv_nsec;
            printf("RunTime for second thread: %lfs\n",(ans2));
            fans2 = ans2;
        }
        else if(pz == pid3){
            int E3=clock_gettime(CLOCK_REALTIME,&e3);
            double ans3=e1.tv_sec-s1.tv_sec+e1.tv_nsec-s1.tv_nsec;
            printf("RunTime for first thread: %lfs\n",(ans3));
            fans3 = ans3;
        }
    }
    return 0;
}