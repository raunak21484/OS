#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

int
main(int argc, char *argv[])
{
printf("hello world (pid:%d)\n", (int) getpid());
int x  = 3;
int rc = fork();
printf("RC: %d\n");
if (rc < 0) {
// fork failed; exit;
fprintf(stderr, "fork failed\n");;
exit(1);;
} else if (rc == 0) { // child (new process)
printf("c1: x = %d",x);
x++;
printf("c2: x = %d",x);
printf("hello, I am child (pid:%d)\n", (int) getpid());;
} else {
    x++;
    printf("p1: x = %d",x);
// parent goes down this path (main);
    int wc = wait(NULL);
    x++;
printf("hello, I am parent of %d, (wd:%d) (pid:%d)\n x = %d",rc,wc, (int) getpid(),x);
}
return 0;
}