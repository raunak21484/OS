#include<dirent.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(int argc, char* argv[])
{
    struct dirent **namelist;
    int n;
    n=scandir(argv[2],&namelist,NULL,alphasort);
    if(n==-1)
    {
        perror("");
        exit(EXIT_FAILURE);
    }
    if(strcmp(argv[1],"-ar")==0 || strcmp(argv[1],"-ra")==0)
    {
        int i=n-1;
        while(i>=0)
        {
            //if(namelist[i]->d_name[0]!='.')
            if(i!=0)
                printf("%s ",namelist[i]->d_name);
            else
                printf("%s\n",namelist[i]->d_name);
            free(namelist[n]);
            i--;
        }
    }
    else if(strcmp(argv[1],"-r")==0)
    {
        int i=n-1;
        while(i>=0)
        {
            if(namelist[i]->d_name[0]!='.')
                {
                printf("%s ",namelist[i]->d_name);
            }
            free(namelist[i]);
            i--;
        }
         printf("\n");
    }
    else if(strcmp(argv[1],"-a")==0)
    {
        int i=0;
        while(i<n)
        {
            //if(namelist[i]->d_name[0]!='.')
            if(i<n-1)
                printf("%s ",namelist[i]->d_name);
            else
                 printf("%s\n",namelist[i]->d_name);
            free(namelist[i]);
            i++;
        } 
    }
    else 
    {
       int i=0;
        while(i<n)
        {
            if(namelist[i]->d_name[0]!='.')
            {
                if(i<n-1)
                    printf("%s ",namelist[i]->d_name);
                else
                    printf("%s\n",namelist[i]->d_name);
            }
            free(namelist[i]);
            i++;
        } 
    }
    free(namelist);
    return 0;
}