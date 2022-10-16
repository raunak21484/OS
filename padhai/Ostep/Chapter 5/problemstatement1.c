#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

int primes[10] = {1,2,3,4,5,6,7,8,9,10};

int i = 0;
pthread_mutex_t lock;
void* printPrime(){
    pthread_mutex_lock(&lock);
    printf("%d <--- \n",primes[i]);
    i++;
    pthread_mutex_unlock(&lock);
}
int main(int argc, char *argv[]){
    pthread_t threads[10];
    pthread_mutex_init(&lock,NULL);
    for(int i=0;i<10;i++){
        pthread_create(&(threads[i]),NULL,&printPrime,NULL);
    }
    for(int i=0;i<10;i++){
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    return 0;
}