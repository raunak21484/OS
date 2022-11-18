#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include<string.h>
#include<dirent.h>
  
int main(int argc, char* argv[]) 
{ 
    char path[100];
    struct stat stats;
    char* cwd;
    cwd=(char*)malloc((RAND_MAX)*sizeof(char));
    getcwd(cwd,RAND_MAX);
    strcpy(path,cwd);
    if(strcmp(path,"/")==0 || strcmp(path,"/home")==0)
    {
        printf("mkdir: cannot create directory: Permission denied.\n");
    }
    else
    {
        struct dirent **namelist;
        int n;
        n=scandir(path,&namelist,NULL,alphasort);
        if(n==-1)
        {
            perror("scandir");
            exit(EXIT_FAILURE);
        }
        else
        {
            for(int t=2;argv[t]!=NULL;t++)
            {
                if(strcmp(argv[1],"-v")==0)
                {
                    int i=0;
                    int flag=0;
                    while(i<n)
                    {
                        if(strcmp(argv[t],namelist[i]->d_name)==0)
                        {
                            flag=1;
                        }
                        i++;
                    }
                    if(!flag)
                    {
                        int check; 
                        char* dirname = argv[t]; 
                        check = mkdir(dirname,0777); 
                        // check if directory is created or not 
                        if (check) 
                        {
                            printf("mkdir: cannot create directory '%s' : No such file or directory\n",argv[t]);   
                        }
                        else
                        {
                            printf("mkdir: created directory '%s'\n",argv[t]);
                        }
                    }
                    else
                    {
                        printf("mkdir: cannot create directory '%s': File exists\n",argv[t]);
                    }
                }
                else if(strcmp(argv[1],"-p")==0)
                {
                  
                   
                    char *direc[100];
                    if(n==-1)
                    {
                        perror("scandir");
                        exit(EXIT_FAILURE);
                    }
                    for(int i=0;;i++)
                    {
                        direc[i]=strsep(&argv[t],"/");
                        if(direc[i]==NULL)
                            break;
                        if(strlen(direc[i])==0)
                            i--;
                    }
                    for(int j=0;direc[j]!=NULL;j++)
                    {
                        int i=0;
                        int flag=0;
                        getcwd(cwd,RAND_MAX);
                        strcpy(path,cwd);
                        n=scandir(path,&namelist,NULL,alphasort);
                        while(i<n)
                        {
                            if(strcmp(direc[j],namelist[i]->d_name)==0)
                            {
                                flag=1;
                            }
                            i++;
                        }
                        if(!flag)
                        {
                            int check; 
                            char* dirname = direc[j]; 
                            check = mkdir(dirname,0777); 
                            // check if directory is created or not 
                            if (check) 
                            {
                                printf("mkdir: cannot create directory '%s' :",direc[j]);   
                            }
                        }
                        else
                        {
                            if(direc[j+1]==NULL)
                                 printf("mkdir: cannot create directory %s: File exists\n",direc[j]);
                        }
                        int x=chdir(direc[j]);
                        getcwd(cwd,RAND_MAX);
                    }
                    //int x=chdir(cwd);
                }
                else if(strcmp(argv[1],"-pv")==0|| strcmp(argv[1],"-vp")==0)
                {
                    char  *direc[100];
                    for(int i=0;;i++)
                    {
                        direc[i]=strsep(&argv[t],"/");
                        if(direc[i]==NULL)
                            break;
                        if(strlen(direc[i])==0)
                            i--;
                    }
                    for(int j=0;direc[j]!=NULL;j++)
                    {
                        int i=0;
                        int flag=0;
                        while(i<n)
                        {
                            if(strcmp(direc[j],namelist[i]->d_name)==0)
                            {
                                flag=1;
                            }
                            i++;
                        }
                        if(!flag)
                        {
                            int check; 
                            char* dirname = direc[j]; 
                            check = mkdir(dirname,0777); 
                            // check if directory is created or not 
                            if (check) 
                            {
                                printf("mkdir: cannot create directory '%s': No such file or directory\n",direc[j]);   
                            }
                            else
                            {
                               printf("mkdir: created directory '%s'\n",direc[j]); 
                            }
                        }
                        int x=chdir(direc[j]);
                        getcwd(cwd,RAND_MAX);
                    }
                   // int x=chdir(cwd);
                }
                else
                {
                    int i=0;
                    int flag=0;
                    while(i<n)
                    {
                        if(strcmp(argv[t],namelist[i]->d_name)==0)
                        {
                            flag=1;
                        }
                        i++;
                    }
                    if(!flag)
                    {
                        int check; 
                        char* dirname = argv[t]; 
                        check = mkdir(dirname,0777); 
                        // check if directory is created or not 
                        if (check) 
                        {
                            printf("mkdir: cannot create directory '%s' : No such file or directory\n",argv[t]);   
                        }
                    }
                    else
                    {
                        printf("mkdir: cannot create directory '%s': File exists\n",argv[t]);
                    }
                }
            }
        }
    }
    return 0;
}