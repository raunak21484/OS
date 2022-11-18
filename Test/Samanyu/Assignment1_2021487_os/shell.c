#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<errno.h> 

void print_user_host_dir()
{
	char* user;
	char* hostname;
	char* cwd;
	user=(char*)malloc(10*sizeof(char));
	hostname=(char*)malloc((_SC_HOST_NAME_MAX+1)*sizeof(char));
	cwd=(char*)malloc((RAND_MAX)*sizeof(char));
	user=getlogin();
	gethostname(hostname,_SC_HOST_NAME_MAX+1);
	getcwd(cwd,RAND_MAX);
	printf("%s@%s:%s$ ",user,hostname,cwd);
}

void add_to_history(char ** cmd,int k,char* storedpath)
{
	FILE *filepointer;
	char stored_path[100]="";
	strcat(stored_path,storedpath);
	strcat(stored_path,"/history.txt");

	filepointer = fopen(stored_path, "a");
	if(filepointer==NULL)
	{
		perror("history file not opened..");
	}
	else
	{
		for(int i=k;cmd[i]!=NULL;i++)
		{
			fputs(cmd[i],filepointer);
			if(cmd[i+1]!=NULL)
				fputs(" ",filepointer);
		}
		if(cmd[1]==NULL)
			fputs("\n",filepointer);
		fclose(filepointer);
	}
}
char find_escape_sequence(char c)
{
	if(c=='a')
		return '\a';
	else if(c=='b')
		return '\b';
	else if(c=='f')
		return '\f';
	else if(c=='n')
		return '\n';
	else if(c=='r')
		return '\r';
	else if(c=='t')
		return '\t';
	else if(c=='v')
		return '\v';
	else if (c=='\0')
		return '0';
	else 
		return c;
}

void make_arr(char** cmd, char** cmd_passed, int size)
{
	cmd_passed[size+2]=NULL;
	int j;
	for(j=size;j>=1;j--)
	{
		int a=sizeof(cmd[j]);
		cmd_passed[j+1]=(char*)malloc(a);
		strcpy(cmd_passed[j+1],cmd[j]);
	}
	//printf("%s\n",cmd_passed[2]);
	cmd_passed[1]=(char*)malloc(5);
	strcpy(cmd_passed[1],"none");
	j=sizeof(cmd[0]);
	cmd_passed[0]=(char*)malloc(j);
	strcpy(cmd_passed[0],cmd[0]);
}
void process_echo(char** cmd)
{
	if(strcmp(cmd[1],"-e")==0)
	{
		for(int j=2;cmd[j]!=NULL;j++)
		{
			if(cmd[j+1]==NULL)
			{
				for(int i=0;i<strlen(cmd[j]);i++)
				{
					if((int)cmd[j][i]!=34 && (int)cmd[j][i]!=39)
					{
						if((int)cmd[j][i]!=92 || ((int)cmd[j][i]==92 && (int)cmd[j][i+1]==92))
						{
							printf("%c",cmd[j][i]);
						}
						else
						{
							//printf("%d",i);
							char h=cmd[j][i+1];
							char d=find_escape_sequence(h);
							printf("%c",d);
							i++;
						}
					}
				}
			}
			else
			{
				for(int i=0;i<strlen(cmd[j]);i++)
				{
					if((int)cmd[j][i]!=34 && (int)cmd[j][i]!=39)
					{
						if((int)cmd[j][i]!=92 || (int)cmd[j][i]==92 && (int)cmd[j][i+1]==92)
						{
							printf("%c",cmd[j][i]);
						}
						else
						{
							//printf("%d",i);
							char h=cmd[j][i+1];
							char d=find_escape_sequence(h);
							printf("%c",d);
							i++;
						}
					}
				}
				printf(" ");	
			}
			
		}
	}

	else if(strcmp(cmd[1],"-n")==0)
	{
		for(int j=2;cmd[j]!=NULL;j++)
		{
			if(cmd[j+1]==NULL)
			{
				for(int i=0;cmd[j][i]!='\n';i++)
				{
					if((int)cmd[j][i]!=34 && (int)cmd[j][i]!=39)
					{
						if((int)cmd[j][i]!=92 || ((int)cmd[j][i]==92 && (int)cmd[j][i+1]==92))
						{
							printf("%c",cmd[j][i]);
						}
					}
				}
			}
			else
			{
				for(int i=0;i<strlen(cmd[j]);i++)
				{
					if((int)cmd[j][i]!=34 && (int)cmd[j][i]!=39)
					{					
						if((int)cmd[j][i]!=92 || ((int)cmd[j][i]==92 && (int)cmd[j][i+1]==92))
						{
							printf("%c",cmd[j][i]);
						}
					}
				}
				printf(" ");	
			}
			
		}
	}
	else
	{
		for(int j=1;cmd[j]!=NULL;j++)
		{
			if(cmd[j+1]==NULL)
			{
				for(int i=0;i<strlen(cmd[j]);i++)
				{
					if((int)cmd[j][i]!=34 && (int)cmd[j][i]!=39)
					{
						if((int)cmd[j][i]!=92 || ((int)cmd[j][i]==92 && (int)cmd[j][i+1]==92))
						{
							printf("%c",cmd[j][i]);
						}
					}
				}
			}
			else
			{
				for(int i=0;i<strlen(cmd[j]);i++)
				{
					if((int)cmd[j][i]!=34 && (int)cmd[j][i]!=39)
					{
						if((int)cmd[j][i]!=92 || ((int)cmd[j][i]==92 && (int)cmd[j][i+1]==92))
						{
							printf("%c",cmd[j][i]);
						}
					}
				}
				printf(" ");	
			}
			
		}
	}

}
void process_history(char** cmd, char* storedpath)
{
	char stored_path[100]="";
	strcat(stored_path,storedpath);
	strcat(stored_path,"/history.txt");
	if(cmd[1]==NULL)
	{
		add_to_history(cmd,0,storedpath);
		FILE *filepointer;
		filepointer=fopen(stored_path,"r");
		if(filepointer==NULL)
		{
			printf("history file unavailable..");
		}
		else
		{
			char data[100];
			while(fgets(data,100,filepointer)!=NULL)
			{
				printf("%s",data);
			}
			fclose(filepointer);
		}
	}
	else if(strcmp(cmd[1],"-c\n")==0)
	{
		int x=remove(stored_path);
		if(x)
		{
			perror("\n");
		}
		else
		{
			FILE *filepointer;
			filepointer = fopen(stored_path, "w");
			fclose(filepointer);
		}
	}
	else if(strcmp(cmd[1],"-s")==0)
	{
		add_to_history(cmd,2,storedpath);
	} 
	else
	{
		add_to_history(cmd,0,storedpath);
		printf("history: invalid option: %s\n",cmd[1]);	
	}
}
void process_pwd(char** cmd)
{
	if(cmd[1]==NULL||strcmp(cmd[1],"-P\n")==0)
	{
	char* pwd;
	pwd=(char*)malloc((RAND_MAX)*sizeof(char));
	getcwd(pwd,RAND_MAX);
	printf("%s\n",pwd);
	}
	else if(strcmp(cmd[1],"-help\n")==0)
	{
	printf("\n\nName:  \npwd - print name of current/working directory\nSynopsis: pwd [OPTION]...\nDescription: Print the full filename of the current working directory.\n\n-P, --physical:  avoid all symlinks\n--help: display this help and exit\n\n");
	}
	else if((cmd[1][0]='-'))
	{
		printf("pwd: invalid flag\n");
	}

}
void process_exit()
{
	exit(0);
}
void process_ls(char **cmd,char* storedpath)
{
	int size;
	char stored_path[100]="";
	strcat(stored_path,storedpath);
	strcat(stored_path,"/ls");
	for(int i=0;cmd[i]!=NULL;i++)
	{
		size=i;
	}
	int length=strlen(cmd[size]);
	if(cmd[1]!=NULL)
		cmd[size][length-1]='\0';
	int status;
	pid_t pid = fork();
	if(pid == 0){
		if(cmd[1]==NULL)
		{
			char* cwd;
			cwd=(char*)malloc((RAND_MAX)*sizeof(char));
			getcwd(cwd,RAND_MAX);
			char* cmd_passed[4];
			cmd_passed[3]=NULL;
			cmd_passed[2]=(char*)malloc((RAND_MAX)*sizeof(char));
			strcpy(cmd_passed[2],cwd);
			cmd_passed[1]=(char*)malloc(5);
			strcpy(cmd_passed[1],"none");
			cmd_passed[0]=(char*)malloc(strlen(cmd[0]));
			strcpy(cmd_passed[0],cmd[0]);
			execv(stored_path, cmd_passed);
			exit(0);
		}
		else if(strcmp(cmd[1],"-r")==0 || strcmp(cmd[1],"-a")==0 || strcmp(cmd[1],"-ra")==0 || strcmp(cmd[1],"-ar")==0)
		{
			if(cmd[2]==NULL)
			{
				char* cmd_passed[4];
				cmd_passed[3]=NULL;
				char* cwd;
				cwd=(char*)malloc((RAND_MAX)*sizeof(char));
				getcwd(cwd,RAND_MAX);
				cmd_passed[2]=(char*)malloc((RAND_MAX)*sizeof(char));
				strcpy(cmd_passed[2],cwd);
				int fsize=strlen(cmd[1]);
				cmd_passed[1]=(char*)malloc(fsize);
				strcpy(cmd_passed[1],cmd[1]);
				cmd_passed[0]=(char*)malloc(strlen(cmd[0]));
				strcpy(cmd_passed[0],cmd[0]);
				execv(stored_path, cmd_passed);
				exit(0);
			}
			else
			{
				char* cmd_passed[4];
				cmd_passed[3]=NULL;
				cmd_passed[2]=(char*)malloc(strlen(cmd[2]));
				strcpy(cmd_passed[2],cmd[2]);
				int fsize=strlen(cmd[1]);
				cmd_passed[1]=(char*)malloc(fsize);
				strcpy(cmd_passed[1],cmd[1]);
				cmd_passed[0]=(char*)malloc(strlen(cmd[0]));
				strcpy(cmd_passed[0],cmd[0]);
				execv(stored_path, cmd_passed);
				exit(0);
			}
		}
		else if(cmd[1][0]=='-')
		{
			printf("ls: invalid option: %s\n",cmd[1]);
			exit(0);
		}
		else
		{
			char* cmd_passed[4];
			cmd_passed[3]=NULL;
			cmd_passed[2]=(char*)malloc(strlen(cmd[1]));
			strcpy(cmd_passed[2],cmd[1]);
			cmd_passed[1]=(char*)malloc(5);
			strcpy(cmd_passed[1],"none");
			cmd_passed[0]=(char*)malloc(strlen(cmd[0]));
			strcpy(cmd_passed[0],cmd[0]);
			execv(stored_path, cmd_passed);
			exit(0);
		}
	}
	else{
		//printf("HI");
		waitpid(pid,&status,0);	
	}
}
void process_cat(char **cmd, char* storedpath)
{
	int size;
	char stored_path[100]="";
	strcat(stored_path,storedpath);
	strcat(stored_path,"/cat");
	for(int i=0;cmd[i]!=NULL;i++)
	{
		size=i;
	}
	if(size!=0)
	{
		int length=strlen(cmd[size]);
		cmd[size][length-1]='\0';
		pid_t pid = fork();
		int status;
		if(pid == 0){
			if(cmd[1]==NULL || strcmp(cmd[1],"-n")==0 || strcmp(cmd[1],"-E")==0 || strcmp(cmd[1],"-En")==0 || strcmp(cmd[1],"-nE")==0)
				execv(stored_path, cmd);
			else
				printf("cat: invalid option: %s\n",cmd[1]);
			exit(0);
			}
		else{
			//printf("HI");
			waitpid(pid,&status,0);
		}
	}
	else
	{
		printf("cat: too few arguments\n");
	}
}
void process_date(char** cmd, char* storedpath)
{
	int size,status;
	char stored_path[100]="";
	strcat(stored_path,storedpath);
	strcat(stored_path,"/date");
	for(int i=0;cmd[i]!=NULL;i++)
	{
		size=i;
	}
	if(size<=1)
	{
		int length=strlen(cmd[size]);
		if(cmd[1]!=NULL)
			cmd[size][length-1]='\0';
		pid_t pid = fork();
		if(pid == 0){
			if(cmd[1]==NULL)
			{
				char* cmd_passed[3];
				cmd_passed[2]=NULL;
				int cmd_size=strlen(cmd[0]);
				cmd_passed[0]=(char*)malloc(cmd_size);
				cmd_passed[1]=(char*)malloc(5);
				strcpy(cmd_passed[1],"none");
				strcpy(cmd_passed[0],cmd[0]);
				execv(stored_path, cmd_passed);
				exit(0);
			}
			else if(strcmp(cmd[1],"-R")==0 || strcmp(cmd[1],"-u")==0 || strcmp(cmd[1],"-Ru")==0 || strcmp(cmd[1],"-uR")==0)
			{
				execv(stored_path, cmd);
				exit(0);
			}
			else
			{
				printf("date: invalid option: %s\n",cmd[1]);
				exit(0);
			}
		}
		else{
		//printf("HI");
		waitpid(pid,&status,0);	
		}
	}
	else
	{
		printf("date: extra operand\n");
	}
}
void process_rm(char **cmd, char* storedpath)
{
	int size,status;
	char stored_path[100]="";
	strcat(stored_path,storedpath);
	strcat(stored_path,"/rm");
	for(int i=0;cmd[i]!=NULL;i++)
	{
		size=i;
	}
	if(size!=0)
	{
		int length=strlen(cmd[size]);
		cmd[size][length-1]='\0';
		pid_t pid = fork();
		if(pid == 0){
			if(strcmp(cmd[1],"-i")==0 || strcmp(cmd[1],"-v")==0 || strcmp(cmd[1],"-vi")==0 || strcmp(cmd[1],"-iv")==0)
				{
					if(size>1)
						execv(stored_path, cmd);
					else
						printf("rm: missing operand\n");
					}
			else if(cmd[1][0]=='-')
			{
				printf("rm: invalid option: %s\n",cmd[1]);
			}
			else
			{
				char* cmd_passed[size+3];
				make_arr(cmd,cmd_passed,size);
				execv(stored_path, cmd_passed);
			}
			exit(0);
		}
		else{
			//printf("HI");
			waitpid(pid,&status,0);
		}
	}
	else
	{
		printf("rm: missing operand\n");
	}
}
void process_mkdir(char **cmd,char* storedpath)
{
	char stored_path[100]="";
	strcat(stored_path,storedpath);
	strcat(stored_path,"/mkdir");
	int size,status;
	for(int i=0;cmd[i]!=NULL;i++)
	{
		size=i;
	}
	if(size!=0)
	{
		int length=strlen(cmd[size]);
		cmd[size][length-1]='\0';
		pid_t pid = fork();
		if(pid == 0){
			if(strcmp(cmd[1],"-v")==0 || strcmp(cmd[1],"-p")==0 || strcmp(cmd[1],"-vp")==0 || strcmp(cmd[1],"-pv")==0)
			{
				if(size!=1)
					execv(stored_path, cmd);
				else
					printf("mkdir: missing arguments\n");
			}
			else if(cmd[1][0]=='-')
			{
				printf("mkdir: invalid option: %s\n",cmd[1]);
			}
			else
			{
				char* cmd_passed[size+3];
				make_arr(cmd,cmd_passed,size);
				execv(stored_path, cmd_passed);
			}
			exit(0);
			}
		else{
			//printf("HI");
			waitpid(pid,&status,0);
		}
	}
	else
	{
		printf("mkdir: missing arguments\n");
	}
}
void process_cd(char** cmd,char* route)
{
	int x;
	if(cmd[1]==NULL || (strcmp(cmd[1],"-P\n")==0 && cmd[2]==NULL))
	{
	getcwd(route,RAND_MAX);
	char* ch=(char*)malloc(10);
	ch=getlogin();
	char path[100]="/home/";
	strcat(path,ch);
	x=chdir(path);	
	}
	else if(strcmp(cmd[1],"-P\n")==0)
	{
		getcwd(route,RAND_MAX);
		int i;
		for(i=0;cmd[2][i]!='\n';i++)
		{
		}
		char* attribute=(char*)malloc(i);
		for(i=0;cmd[2][i]!='\n';i++)
		{
			attribute[i]=cmd[2][i];
		}
		x=chdir(attribute);
	}
	else if(strcmp(cmd[1],"-\n")==0)
	{
		if(strcmp(route,"none")==0)
		{
			printf("cd: OLDPWD not set\n");
		}
		else
		{
			printf("%s\n",route);
		}	
		x=0;
	}
	else if(cmd[1][0]=='-')
	{
		printf("cd: invalid option\n");
		x=0;
	}
	else
	{	
		getcwd(route,RAND_MAX);
		int i;
		for(i=0;cmd[1][i]!='\n';i++)
		{
		}
		char* attribute=(char*)malloc(i);
		for(i=0;cmd[1][i]!='\n';i++)
		{
			attribute[i]=cmd[1][i];
		}
		x=chdir(attribute);
	}	
	if(x!=0)
	{
		perror("");
	}
}
void process_command(char** cmd,char* stored_path, char* route)
{
	if(cmd[1]==NULL)
	{
		int size=strlen(cmd[0]);
		cmd[0][size-1]='\0';
		//printf("%d\n",size );
	}
	if(strcmp(cmd[0],"cd")==0)
	{
		process_cd(cmd,route);
		add_to_history(cmd,0,stored_path);
	}
	else if(strcmp(cmd[0],"echo")==0)
	{
		process_echo(cmd);
		add_to_history(cmd,0,stored_path);
	}
	else if(strcmp(cmd[0],"history")==0)
	{
		process_history(cmd,stored_path);
	}
	else if(strcmp(cmd[0],"pwd")==0)
	{
		process_pwd(cmd);
		add_to_history(cmd,0,stored_path);
	}
	else if(strcmp(cmd[0],"exit")==0)
	{
		add_to_history(cmd,0,stored_path);
		process_exit();
	}
	else if(strcmp(cmd[0],"ls")==0)
	{
		process_ls(cmd,stored_path);
		add_to_history(cmd,0,stored_path);
	}
	else if(strcmp(cmd[0],"cat")==0)
	{
		process_cat(cmd,stored_path);
		add_to_history(cmd,0,stored_path);
	}
	else if(strcmp(cmd[0],"date")==0)
	{
		process_date(cmd,stored_path);
		add_to_history(cmd,0,stored_path);
	}
	else if(strcmp(cmd[0],"rm")==0)
	{
		process_rm(cmd,stored_path);
		add_to_history(cmd,0,stored_path);
	}
	else if(strcmp(cmd[0],"mkdir")==0)
	{
		process_mkdir(cmd,stored_path);
		add_to_history(cmd,0,stored_path);
	}
	else
	{
		printf("command %s not found.\n",cmd[0]);
	}
}

void process_string(char* command, char* stored_path,char* route)
{
	char* cmd[100];
	for(int i=0;;i++)
	{
		cmd[i]=strsep(&command," ");
		if(cmd[i]==NULL)
			break;
		if(strlen(cmd[i])==0)
			i--;
	}
	process_command(cmd,stored_path,route);
}
int main()
{
	char stored_path[100]="";
	char* cwd;
	cwd=(char*)malloc((RAND_MAX)*sizeof(char));
	getcwd(cwd,RAND_MAX);
	strcat(stored_path,cwd);
	int l=1;
	char* route=(char*)malloc((RAND_MAX)*sizeof(char));
	strcpy(route,"none");
	printf("\n\n-------------WELCOME TO SAMANYU'S SHELL--------------\n--> By: Samanyu Kamra      \t\t\t       --> Rollno.-2021487 \n\n      xxxxxxxxxxxxx....USE AT OWN RISK...xxxxxxxxxxxx\n\n");
	while(l)
	{
		print_user_host_dir();
		char command[100];
		fgets(command, 100, stdin);

		//printf("%s",command);
		process_string(command,stored_path,route);
	}
}