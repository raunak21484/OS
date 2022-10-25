#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include <stdbool.h>
char **inpt()
{
    int n = 0;
    int c = 16;
    char *input_line = NULL;
    size_t size = 0;
    ssize_t strlen = getline(&input_line, &size, stdin);
    char **split_input = malloc(c * sizeof(char *));
    char *d = " \t\r\n";
    char *l = strtok(input_line, d);
    while (l != NULL)
    {
        split_input[n] = l;
        n++;
        if (n >= c)
        {
            c = (c * 2);
            split_input = realloc(split_input, c * sizeof(char *));
        }
        l = strtok(NULL, d);
    }
    split_input[n] = NULL;
    return split_input;
}

void executing(char **args)
{
    if (strcmp(args[0], "cd"))
    {
        if (strcmp(args[1], ".."))
        {
            chdir("..");
        }
        else if (strcmp(args[1], "") == 0 || strcmp(args[1], "~") == 0)
        {
            chdir(getenv("HOME"));
        }
        else if (strcmp(args[1], "-L") == 0)
        {
            chdir(args[2]);
        }
        else if (strcmp(args[1], "-P") == 0)
        {
            chdir(args[2]);
        }
    }
    else if (strcmp(args[0], "pwd"))
    {
        if (args[1]!=NULL && strcmp(args[1], "-L") == 0)
        {
            char ss[400];
            printf("%s\n", getcwd(ss, 400));
        }

        else if (args[1]==NULL)
        {
            char ss[400];
            printf("%s\n", getcwd(ss, 400));
        }
    }
    // else if (strcmp(args[0], "echo"))
    // {
    // }

    // pid_t pid = fork();
    // if (pid < 0)
    // {
    //     printf("Fork failed\n");
    //     exit(1);
    // }
    // else if (pid == 0)
    // {
    //     execvp(args[0], args);
    //     printf("there is some error");
    //     exit(1);
    // }
    // else
    // {
    //     wait(NULL);
    // }
}
int main()
{
    printf("---------------Sridhar's Shell-----------------\n");
    while (true)
    {

        printf("$ ");
        char **split_input = inpt();
        // char *input = strtok(split_input, "\n");
        if (split_input[0] != NULL)
        {
            executing(split_input);
        }
        free(split_input);
    }
}