#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[])
{
	FILE *filepointer;
	if(strcmp(argv[1],"-n")==0)
	{
		int line=0;
		if(argc>2)
		{
			for(int i=2;i<argc;i++)
			{
				filepointer = fopen(argv[i], "r");
				if(filepointer==NULL)
				{
					perror("");
				}
				else
				{
					char data[1000];
					while(fgets(data,1000,filepointer)!=NULL)
					{
						line=line+1;
						printf("%d ",line);
						printf("%s",data);
					}
					fclose(filepointer);
				}
			}
		}
		else
		{
			printf("cat: too few arguments\n");
		}
	}
	else if(strcmp(argv[1],"-E")==0)
	{	
		if(argc>2)
		{
			for(int i=2;i<argc;i++)
			{
				filepointer = fopen(argv[i], "r");
				if(filepointer==NULL)
				{
					perror("");
				}
				else
				{
					char data[1000];
					while(fgets(data,1000,filepointer)!=NULL)
					{
						int size=strlen(data);
						data[size-1]='\0';
						printf("%s",data);
						printf("%c\n",'$');
					}
					fclose(filepointer);
				}
			}
		}
		else
		{
			printf("cat: too few arguments\n");
		}
	}
	else if(strcmp(argv[1],"-En")==0 || strcmp(argv[1],"-nE")==0)
	{
		int line=0;
		if(argc>2)
		{
		for(int i=2;i<argc;i++)
			{
				filepointer = fopen(argv[i], "r");
				if(filepointer==NULL)
				{
					perror("");
				}
				else
				{
					char data[1000];
					while(fgets(data,1000,filepointer)!=NULL)
					{
						line=line+1;
						int size=strlen(data);
						data[size-1]='\0';
						printf("%d ",line);
						printf("%s",data);
						printf("%c\n",'$');
					}
					fclose(filepointer);
				}
			}
		}
		else
		{
			printf("cat: too few arguments\n");
		}
	}
	else
	{
		for(int i=1;i<argc;i++)
		{
			filepointer = fopen(argv[i], "r");
			if(filepointer==NULL)
			{
				perror("");
			}
			else
			{
				char data[1000];
				while(fgets(data,1000,filepointer)!=NULL)
				{
					printf("%s",data);
				}
				fclose(filepointer);
			}
		}
	}
	return 0;
}