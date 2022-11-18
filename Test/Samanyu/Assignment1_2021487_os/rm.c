#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
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
    	printf("rm: cannot remove: Permission denied.\n");
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
	    	for(int j=2;j<argc;j++)
	    	{
		    	int i=0;
		    	int flag=0;
		    	while(i<n)
		    	{
		    		if(strcmp(argv[j],namelist[i]->d_name)==0)
		    		{
		    			flag=1;
		    			if(namelist[i]->d_type==DT_DIR)
		    				flag=2;
		    		}
		    		i++;
		    	}
		    	if(flag==1)
		    	{
		    		if(strcmp(argv[1],"-v")==0)
		    		{
		    			int x=remove(argv[j]);
		    			if(x)
		    			{
		    				perror("\n");
		    			}
		    			else
		    			{
		    				printf("removed %s\n",argv[j]);
		    			}
		    		}
		    		else if(strcmp(argv[1],"-i")==0)
		    		{
		    			char choice[2];
		    			printf("rm: remove file '%s'? ",argv[j]);
		    			scanf("%s",choice);
		    			if(choice[0]=='y'||choice[0]=='Y')
		    			{
		    				int x=remove(argv[j]);
		    				if(x)
		    					perror("\n");
		    			}
		    		}
		    		else if(strcmp(argv[1],"-vi")==0 || strcmp(argv[1],"-iv")==0)
		    		{
		    			char choice[2];
		    			printf("rm: remove file '%s'? ",argv[j]);
		    			scanf("%s",choice);
		    			if(choice[0]=='y'||choice[0]=='Y')
		    			{
		    				int x=remove(argv[j]);
		    				if(x)
			    			{
			    				perror("\n");
			    			}
			    			else
			    			{
			    				printf("removed %s\n",argv[j]);
			    			}
		    			}

		    		}
			    	else
			    	{
			    		int x=remove(argv[j]);
			    	}
		    	}
		    	else if(flag==0)
		    	{
		    		printf("rm: cannot remove '%s': No such file or directory\n",argv[j]);
		    	}
		    	else
		    	{
		    		printf("rm: cannot remove '%s': Is a directory\n",argv[j]);
		    	}
		    }
    	}
    }
    return 0;
}