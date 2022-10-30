#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<libgen.h>
#include<pthread.h>


void echols(char** segment){
    int ptr =1;
    int EOL = 1;
    if(segment[1] != NULL){
        if(strcmp(segment[1],"-n")==0 || strcmp(segment[1],"-n\n")==0){
            EOL = 0;
            ptr = 2;
        }else if(strcmp(segment[1],"-E")==0 || strcmp(segment[1],"-E\n")==0){
            ptr = 2;
        }
    }
    int marking = -1, dollarmarking = -1;
    while(segment[ptr]!=NULL){
        int ptr2 = 0;
        marking = -1;dollarmarking=-1;
        while(segment[ptr][ptr2]!='\0'){
            if(segment[ptr][ptr2]=='\\'){
                if(segment[ptr][ptr2+1]=='\\' && marking!= ptr2){
                    marking = ptr2+1;
                    printf("%c",'\\');}
                ptr2++;
                continue;
            }
            if(segment[ptr][ptr2]=='$'){
                if(segment[ptr][ptr2+1]=='$' && dollarmarking!=ptr2){
                    dollarmarking = ptr2+1;
                    printf("%d",(int)getpid());
                }
                ptr2++;
                continue;
            }
            if(segment[ptr+1]==NULL && segment[ptr][ptr2]=='\n' && EOL==0){
                ptr2++;
            }
            printf("%c",segment[ptr][ptr2]);
            ptr2++;
        }
        ptr++;
        if(segment[ptr]!=NULL){printf(" ");}
    }
}
char* echoMessagemkdir(char** segment, int ptr, char sep){
    int EOL = 0;
    int tsize =0;
    int tptr = ptr;
    while(segment[tptr]!=NULL){tsize+=strlen(segment[tptr]);tptr++;}
//    printf("TSIZE: %d\n",tsize);
    char * ECHOMESSAGE = (char*)malloc((tsize*2) * sizeof(char));
    int eptr = 0;
    int marking = -1, dollarmarking = -1;

    while(segment[ptr]!=NULL){
        //printf("Segment[%d] raunak114 = %s\n",ptr,segment[ptr]);
        int ptr2 = 0;
        marking = -1;dollarmarking=-1;
        while(segment[ptr][ptr2]!='\0'){

            if(segment[ptr][ptr2]=='\\'){
                //printf("FOUND1!!");
                if(segment[ptr][ptr2+1]=='\\' && marking!= ptr2){
                    marking = ptr2+1;
                    //printf("%c",'\\');
                    ECHOMESSAGE[eptr] = '\\';
                    eptr++;
                }
                ptr2++;
                continue;
            }
            if(segment[ptr][ptr2]=='$'){
                //printf("FOUND2!");
                ECHOMESSAGE[eptr] = '$';
                eptr++;
                if(segment[ptr][ptr2+1]=='$' && dollarmarking!=ptr2){
                    dollarmarking = ptr2+1;
                    //printf("%d",(int)getpid());
                }
                ptr2++;
                continue;
            }
            if(segment[ptr+1]==NULL && segment[ptr][ptr2]=='\n' && EOL==0){
                //printf("HERE");
                ptr2++;
            }
            //printf("%c",segment[ptr][ptr2]);
            ECHOMESSAGE[eptr] = segment[ptr][ptr2];
            ptr2++;

            eptr++;
        }
        ptr++;
        if(segment[ptr]!=NULL){ECHOMESSAGE[eptr] = sep; eptr++;}
    }
    ECHOMESSAGE[eptr] = '\0';
    //printf("EPTR = %d",eptr);
//    printf("\nMessage: \n");
//    for(int i=0;i<eptr;i++){
//        printf("'%c' ",ECHOMESSAGE[i]);
//    }
    return ECHOMESSAGE;
}
char * _PROGRAM_DIRECTORY;
char ** getSplittedLine(char* line, char* delim){
    int cap = 16;
    int len = 0;
    char **tokens = malloc(sizeof(char*) *cap );
    char *tokentemp = strtok(line, delim);

    while (tokentemp!=NULL) {
        tokens[len++] = tokentemp;
        if (len >= cap) {
            cap*=(int)1.75;
            tokens = realloc(tokens, cap * sizeof(char*));
        }
        tokentemp = strtok(NULL, delim);
    }
    tokens[len] = NULL;

    return tokens;
}
char **getInput(){
    char *line = NULL;
    size_t l = 0;
    getline(&line,&l,stdin);
    if(line[0]=='\n' && line[1]=='\0'){return NULL;}
    return getSplittedLine(line," ");
}
void echo(char** segment){
    int ptr =1;
    int EOL = 1;
    if(segment[1] != NULL){
        if(strcmp(segment[1],"-n")==0 || strcmp(segment[1],"-n\n")==0){
            EOL = 0;
            ptr = 2;
        }else if(strcmp(segment[1],"-E")==0 || strcmp(segment[1],"-E\n")==0){
            ptr = 2;
        }
    }
    int marking = -1, dollarmarking = -1;
    while(segment[ptr]!=NULL){
        int ptr2 = 0;
        marking = -1;dollarmarking=-1;
        while(segment[ptr][ptr2]!='\0'){
            if(segment[ptr][ptr2]=='\\'){
                if(segment[ptr][ptr2+1]!='\0' && marking!= ptr2){
                    marking = ptr2+1;
                    printf("%c",segment[ptr][ptr2+1]);
                ptr2++;
                }
//                else if(segment[ptr][ptr2+1]=='\0'){
//                    printf(" ");
//                }
                ptr2++;
                continue;
            }
            if(segment[ptr][ptr2]=='$'){
                if(segment[ptr][ptr2+1]=='$' && dollarmarking!=ptr2){
                    dollarmarking = ptr2+1;
                    printf("%d",(int)getpid());
                }
                ptr2++;
                continue;
            }
            if(segment[ptr+1]==NULL && segment[ptr][ptr2]=='\n' && EOL==0){
                ptr2++;
            }

            printf("%c",segment[ptr][ptr2]);
            ptr2++;
        }
        ptr++;
        if(segment[ptr]!=NULL){printf(" ");}
    }
}
char* echoMessage(char** segment, int ptr, char sep){
    int EOL = 0;
    int tsize =0;
    int tptr = ptr;
    while(segment[tptr]!=NULL){tsize+=strlen(segment[tptr]);tptr++;}
//    printf("TSIZE: %d\n",tsize);
    char * ECHOMESSAGE = (char*)malloc((tsize*3+3) * sizeof(char));
    int eptr = 0;
    int marking = -1, dollarmarking = -1;

    while(segment[ptr]!=NULL){
        //printf("Segment[%d] raunak114 = %s\n",ptr,segment[ptr]);
        int ptr2 = 0;
        marking = -1;dollarmarking=-1;
        while(segment[ptr][ptr2]!='\0'){

            if(segment[ptr][ptr2]=='\\'){
                //printf("FOUND1!!");
                if(segment[ptr][ptr2+1]!='\0' && marking!= ptr2){
                    marking = ptr2+1;
                    //printf("%c",'\\');
                    ECHOMESSAGE[eptr] = segment[ptr][ptr2+1];
                    eptr++;
                    ptr2++;
                }
//                else if(segment[ptr][ptr2+1]=='\0'){
//                    ECHOMESSAGE[eptr] = ' ';
//                    eptr++;
//                }
                ptr2++;
                continue;
            }
            if(segment[ptr][ptr2]=='$'){
                //printf("FOUND2!");
                ECHOMESSAGE[eptr] = '$';
                eptr++;
                if(segment[ptr][ptr2+1]=='$' && dollarmarking!=ptr2){
                    dollarmarking = ptr2+1;
                    //printf("%d",(int)getpid());
                }
                ptr2++;
                continue;
            }
            if(segment[ptr+1]==NULL && segment[ptr][ptr2]=='\n' && EOL==0){
                //printf("HERE");
                ptr2++;
            }
            //printf("%c",segment[ptr][ptr2]);
            ECHOMESSAGE[eptr] = segment[ptr][ptr2];
            ptr2++;

            eptr++;
        }
        ptr++;
        if(segment[ptr]!=NULL){ECHOMESSAGE[eptr] = sep; eptr++;}
    }
    ECHOMESSAGE[eptr] = '\0';
    //printf("EPTR = %d",eptr);
//    printf("\nMessage: \n");
//    for(int i=0;i<eptr;i++){
//        printf("'%c' ",ECHOMESSAGE[i]);
//    }
    return ECHOMESSAGE;
}
char* delim(char* input){
    char *input2 = strtok(input,"\n");
    return input2;
}
void changeDir(char ** segment){
    int c =0,ptr1 =1;
    int tptr = 0;
    int firstarg = 1,nol =0;
    while(segment[ptr1]!=NULL){
        tptr = 0;
        while(segment[ptr1][tptr]!='\0'){
            c++;
            tptr++;
        }

        if(firstarg <=3 && nol==0 && (strcmp(segment[ptr1],"-P")==0|| strcmp(segment[ptr1],"-P\n")==0|| strcmp(segment[ptr1],"-L")==0|| strcmp(segment[ptr1],"-L")==0)){
            firstarg++;
        }else{
            nol = 1;
        }
        ptr1++;
        c++;
    }
    //printf("%d <-- firstarg\n",firstarg);
    if(ptr1==firstarg || (strcmp(segment[1],"\n")==0)){
        chdir("/home");
        return;
    }
    if(strcmp(segment[1],"~")==0 || strcmp(segment[1],"~\n")==0){
        chdir("/root");
        return;
    }
    //printf("segment[1] is '%s'\n",segment[1]);
    char* newDir = (char*)malloc((c+1)*sizeof(char));
    newDir[c] = '\0';
    ptr1 = firstarg;
    c=0;
    while(segment[ptr1]!=0){
        tptr = 0;
        while(segment[ptr1][tptr]!='\0'){
            newDir[c] = segment[ptr1][tptr];
            c++;
            tptr++;
        }
        ptr1++;
        newDir[c] = ' ';
        c++;
    }
    char * temp = delim(newDir);
    //printf("Temp = %s\n",temp);
    int fin = chdir(temp);
    if(fin!=0){
        printf("Could not find directory: %s\n",temp);
    }
    free(temp);

}
char* getPWD(){
    char* buffer = NULL;
    size_t size = 0;
    return getcwd(buffer,size);
}
char* delimslash(char * input){
    return strtok(input,"/");
}
char * concatString(char * string1, char * string2){

    int c1 = (string1!=NULL?strlen(string1):0);
    int c2 = (string2!=NULL?strlen(string2):0);
    int c = c1+c2;
    //printf("c = %d\n",c);
    char* stringfinal = (char*)malloc(sizeof(char)*(c+1));

    for(int i=0;i< c1;i++){
        stringfinal[i] = string1[i];
    }

    for(int i=0;i< c2;i++){
        stringfinal[i+ c1] = string2[i];
    }
    stringfinal[c] = '\0';
    //printf("here");
    //printf("stringfinal = %s\n",stringfinal);
    return stringfinal;
}
int call_mkdir(char* path){
    pid_t proc = fork();//raunak114
    if (proc < 0) {
        printf("Failed!\n");
        return 2;
    }
    if (proc == 0) {
//        char* tempDir;
//        strcpy(tempDir,_PROGRAM_DIRECTORY);
//        printf("\nTEMPDIR: %s\nPROGRAMDIR: %s\n",tempDir,_PROGRAM_DIRECTORY);
        char* mkname = concatString(_PROGRAM_DIRECTORY,"/mkdir.o");
        //char* mkname = strcat(_PROGRAM_DIRECTORY,"/mkdir.o");

        //printf("MKNAME = %s\n",mkname);
        char* pwd = getPWD();
        char* arr[4] = {mkname,path,pwd,NULL};
        //printf("PATH = %s\n",path);
        char * env[1] = {NULL};

        execve(mkname,arr,env);
        return 3;

    } else {
        int status;
        wait(&status);
        return status;
    }
}
void date(char ** segment){
    int fid = fork();
    if(fid<0){printf("Failed due to unexpected error1!\n");return;}
    if(fid==0){
        //char* tempDIR;
        //strcpy(tempDIR,_PROGRAM_DIRECTORY);
//        char* mkname = raunak(_PROGRAM_DIRECTORY,"/date.o");
        char* mkname = concatString(_PROGRAM_DIRECTORY,"/date.o");
        if(segment[1]==NULL || strcmp(segment[1],"-u")==0 || strcmp(segment[1],"--utc")==0 || strcmp(segment[1],"--universal")==0 ||
                                    strcmp(segment[1],"-u\n")==0 || strcmp(segment[1],"--utc\n")==0 || strcmp(segment[1],"--universal\n")==0||strcmp(segment[1],"\n")==0){
            //segment[0][strlen(segment[0])-1] = '\0';
            //printf("in HEREEE!!");
            char* argv[3]=  {mkname,"default",NULL};
            char* env[1] = {NULL};
            //printf("mkname = %s, location = %p\n",mkname,mkname);
            execve(mkname,argv,env);
        }else if(strcmp(segment[1],"-R")==0 || strcmp(segment[1],"--rfc-email")==0  || strcmp(segment[1],"-R\n")==0 || strcmp(segment[1],"--rfc-email\n")==0){
                printf("in here!!!");
            char *argv[3] = {mkname,"r",NULL};
                char* env[1] = {NULL};
                execve(mkname,argv,env);
            }
        char * temp = echoMessage(segment,0,'|');
        printf("seg: %s\n",temp);
        printf("Failed due to unexpected error2!\n");
        return;
    }else{
        int status;
        wait(&status);
        if(status!=0){printf("Failed due to unexpected error3!\n");}
    }
}
void mkdir1(char ** segment){
    if(segment[1]!=NULL) {
        if(strcmp(segment[1],"\n")==0 || strcmp(segment[1]," ") == 0){return;}
        else if(strcmp(segment[1],"-v")==0){
            char* message = echoMessagemkdir(segment,2,' ');
            int stat =call_mkdir(message);
            //printf("\nstat = %d\n",stat);//
            if(stat==0){
                printf("Created Directory: %s\n",message);
            }else{
                printf("Creation of directory failed!\n");
            }

        }else if(strcmp(segment[1],"-v\n")==0 || strcmp(segment[1],"-p\n")==0){
            printf("mkdir: Missing operand\n");
        }else if(strcmp(segment[1],"-p")==0){
            char* message = echoMessagemkdir(segment,2,' ');
            char** segmentTWO = getSplittedLine(message,"/");
            int c =0;
            for(int i=0;segmentTWO[i]!=NULL;i++){
                c+=strlen(segmentTWO[i]);
            }
            char * temp = (char*)malloc(sizeof(char)*(2*c+1));
            int ptr = 0;
            for(int i=0;segmentTWO[i]!=NULL;i++){
                printf("%s\n",segmentTWO[i]);
                for(int j=0;j<strlen(segmentTWO[i]);j++){
                    temp[ptr] = segmentTWO[i][j];
                    ptr++;
                }
                temp[ptr] = '/';
                ptr++;
                temp[ptr+1] = '\0';
                //strncat(temp,segmentTWO[i],strlen(segmentTWO[i]));
                if(call_mkdir(temp)!=0){
                    printf("ERROR, temp = %d\n",temp);
                }
            }
            free(temp);
        }else{
            //printf("DEFAULT");
            char* message = echoMessagemkdir(segment,1,' ');
            if(call_mkdir(message)!=0){ printf("Creation of directory failed!\n");}
            //MAKE DIRECTORY NORMALLY
        }

    }
}
void ls(char ** segment){

        char* mkname = concatString(_PROGRAM_DIRECTORY,"/ls.o");
        int fid = fork();
        if(fid<0){
            printf("Failed!");
            return;
        }
        if(fid==0){
            char* env[1] = {NULL};
            if(segment[1]==NULL){
                char * argv[4] = {mkname,"00",getPWD(),NULL};
                execve(mkname,argv,env);
                printf("Failed due to unexpected error! Code = -1\n");
            }
            else if(strcmp(segment[1],"-m")==0 || strcmp(segment[1],"-m\n")==0){
                if(segment[2] == NULL){
                    char* argv[4] = {mkname,"01",getPWD(),NULL};
                    execve(mkname, argv,env);
                    printf("Failed due to unexpected error! Code = -2\n");

                }
                else if(strcmp(segment[2],"-a")==0 || strcmp(segment[2],"-a\n")==0){
                    if(segment[3]==NULL){
                        char* argv[4] = {mkname,"11",getPWD(),NULL};
                        execve(mkname, argv,env);
                        printf("Failed due to unexpected error! Code = -3\n");
                    }
                    else{
                        char * ccat1 = concatString(getPWD(),"/");
                        char* ccat = concatString(ccat1, echoMessage(segment,3,' '));
                        char* argv[4]  = {mkname, "11",ccat,NULL};
                        execve(mkname,argv,env);
                        printf("Failed due to unexpected error! Code = -4\n");
                    }
                }
                else{
                    char * ccat1 = concatString(getPWD(),"/");
                    char* ccat = concatString(ccat1, echoMessage(segment,2,' '));
                    char* argv[4]  = {mkname, "01",ccat,NULL};
                    execve(mkname,argv,env);
                    printf("Failed due to unexpected error! Code = -5\n");
                }
            }
            else if(strcmp(segment[1],"-a")==0 || strcmp(segment[1],"-a\n")==0){
                if(segment[2] == NULL){
                    char* argv[4] = {mkname,"10",getPWD(),NULL};
                    execve(mkname, argv,env);
                    printf("Failed due to unexpected error! Code = -6\n");

                }
                else if(strcmp(segment[2],"-m")==0 || strcmp(segment[2],"-m\n")==0){
                    if(segment[3]==NULL){
                        char* argv[4] = {mkname,"11",getPWD(),NULL};
                        execve(mkname, argv,env);
                        printf("Failed due to unexpected error! Code = -7\n");
                    }else{
                        char * ccat1 = concatString(getPWD(),"/");
                        char* ccat = concatString(ccat1, echoMessage(segment,3,' '));
                        char* argv[4]  = {mkname, "11",ccat,NULL};
                        execve(mkname,argv,env);
                        printf("Failed due to unexpected error! Code = -8\n");
                    }
                }
                else{
                    char * ccat1 = concatString(getPWD(),"/");
                    char* ccat = concatString(ccat1, echoMessage(segment,2,' '));
                    char* argv[4]  = {mkname, "10",ccat,NULL};
                    execve(mkname,argv,env);
                    printf("Failed due to unexpected error! Code = -9\n");
                }
            }
            else{
                char * ccat1 = concatString(getPWD(),"/");
                char* ccat = concatString(ccat1, echoMessage(segment,1,' '));
                char* argv[4]  = {mkname, "00",ccat,NULL};
                execve(mkname,argv,env);
                printf("Failed due to unexpected error! Code = -10\n");
            }
        }
        else{
            int status;
            wait(&status);
            //if(status!=0){printf("Failed due to unexpected error! Code = %d |\n",status);}
            if(status!=0){printf("Directory Does not exist!\n");}
        }

}
void rm(char ** segment){
    if(segment[1]==NULL){
        printf("Missing Operand\n");
        return;
    }
    int force = 0,sucmes =0;
    if(strcmp(segment[1],"-f")==0 || strcmp(segment[1],"-f\n")==0 || (segment[2]!=NULL && (strcmp(segment[2],"-f")==0 || strcmp(segment[2],"-f\n")==0 ))){
        force = 1;
    }
    if(strcmp(segment[1],"-v")==0 || strcmp(segment[1],"-v\n")==0 || (segment[2]!=NULL && (strcmp(segment[2],"-v")==0 || strcmp(segment[2],"-v\n")==0 ))){
        sucmes = 1;
    }
    if(force+sucmes== 1 && segment[1][0]!='-'){
        printf("Please place all flags at the beginning!\n");
        return;
    }
    int pid = fork();
    if(pid<0){
        printf("Failed to fork!\n");
        return;
    }if(pid==0){
        char * fpath = concatString(_PROGRAM_DIRECTORY,"/");
        char* mkname = concatString(_PROGRAM_DIRECTORY,"/rm.o");
        char* pathfinal = concatString(fpath, echoMessage(segment,force+sucmes+1,' '));
        char* argv[3] = {mkname,pathfinal,NULL};
        char* env[1] = {NULL};
        execve(mkname,argv,env);
        printf("FAILED 1");
        return;
    }else{
        int status;
        wait(&status);
        if(status!=0){
            if(force==1){
                return;
            }else{
                printf("File does not exist!\n");
            }
        }else if(sucmes==1){
            printf("File deleted Successfully!\n");
        }
    }
}
void cat(char ** segment){
    if(segment[1]==NULL){
        printf("Please Enter a file name!\n");
        return;
    }
    char flags[2] = "00";//T,N
    if(strcmp(segment[1],"-T")==0 ||strcmp(segment[1],"-T\n")==0 || (segment[2]!=NULL && (strcmp(segment[2],"-T")==0 ||strcmp(segment[2],"-T\n")==0))){
        flags[0] ='1';
    }
    if(strcmp(segment[1],"-n")==0 ||strcmp(segment[1],"-n\n")==0 || (segment[2]!=NULL && (strcmp(segment[2],"-n")==0 ||strcmp(segment[2],"-n\n")==0))){
        flags[1] = '1';
    }
    if(flags[1]+flags[0]- 2*'0'==1 && segment[1][0]!='-'){
        printf("Please start the command with all the flags!\n");
        return;
    }
    int c=0;
    while(segment[c]!=NULL){c++;}
//    printf("Segment: ");
//    for(int i=0;segment[i]!=NULL;i++){
//        printf("'%s'\n",segment[i]);
//    }
    char* mkname = concatString(_PROGRAM_DIRECTORY,"/cat.o");
    int pid = fork();
    if(pid<0){
        printf("Forking error!\n");
        return;
    }
    if(pid==0){
        char** argv = (char**)malloc(sizeof(char*)*(c+5));
        argv[0] = mkname;
        argv[1] = flags;
        argv[2] = concatString(getPWD(),"/");
        int ptr = 3;
        for(int i=flags[1]+flags[0]-2*'0'+1;segment[i]!=NULL;i++){
            argv[ptr]= segment[i];
            ptr++;
        }
        argv[ptr] = NULL;
        char* env[1] = {NULL};
        execve(mkname, argv, env);
        printf("Unknown error!\n");
        return;
    }else{
        int status;
        wait(&status);
        if(status!=0){
            printf("Unknown error occured!\n");
        }
    }
}
char * getfstring(char** args){
    printf("args[2] = %s\n",args[2]);
    int c =0;
    for(int i=0;args[i]!=NULL;i++){
        c+=strlen(args[i]);
    }
    c*=4;
    printf("c = %d\n\n\n",c);
    char* fstring = (char*)malloc(sizeof(char)*(c+10));
    int ptr = 0;
    for(int i=0;args[0][i]!='&' && args[0][i]!='\0';i++){
        if(args[0][i]==' '){
            fstring[ptr] = '\\';
            ptr++;
        }
        fstring[ptr] = args[0][i];
        ptr++;
    }
    fstring[ptr++] = ' ';
    printf("After initial command, string = '%s'\n",fstring);//
    for(int i=1;args[i]!=NULL;i++){
        if(i==2){printf("Here is arg[2]: ");}
        for(int j=0;j<args[i][j]!='\0';j++){
            if(i==2){
                printf("%c",args[i][j]);
            }
            if(args[i][j]==' '){
                fstring[ptr] = '\\';
                ptr++;
            }
            fstring[ptr] = args[i][j];
            ptr++;
        }
        fstring[ptr] = ' ';
        ptr++;
        if(i==2){printf("\n\n");}
    }
    fstring[ptr] = '\0';
    printf("Final system call: '%s'\n",fstring);
    return fstring;
}
void* syscall1(void* fstring){
    system((char*)fstring);
}
void catthread(char** segment){
    if(segment[1]==NULL){
        printf("Please Enter a file name!\n");
        return;
    }
    char flags[2] = "00";//T,N
    if(strcmp(segment[1],"-T")==0 ||strcmp(segment[1],"-T\n")==0 || (segment[2]!=NULL && (strcmp(segment[2],"-T")==0 ||strcmp(segment[2],"-T\n")==0))){
        flags[0] ='1';
    }
    if(strcmp(segment[1],"-n")==0 ||strcmp(segment[1],"-n\n")==0 || (segment[2]!=NULL && (strcmp(segment[2],"-n")==0 ||strcmp(segment[2],"-n\n")==0))){
        flags[1] = '1';
    }
    if(flags[1]+flags[0]- 2*'0'==1 && segment[1][0]!='-'){
        printf("Please start the command with all the flags!\n");
        return;
    }
    int c=0;
    while(segment[c]!=NULL){c++;}
//    printf("Segment: ");
//    for(int i=0;segment[i]!=NULL;i++){
//        printf("'%s'\n",segment[i]);
//    }
    char* mkname = concatString(_PROGRAM_DIRECTORY,"/cat.o");
        char** argv = (char**)malloc(sizeof(char*)*(c+5));
        argv[0] = mkname;
        argv[1] = flags;
        argv[2] = concatString(getPWD(),"/");
        int ptr = 3;
        for(int i=flags[1]+flags[0]-2*'0'+1;segment[i]!=NULL;i++){
            argv[ptr]= segment[i];
            ptr++;
        }
        argv[ptr] = NULL;
        char* env[1] = {NULL};
//        execve(mkname, argv, env);
        pthread_t id;
        printf("argv[2] = '%s'\n",argv[2]);
        char* t1 = getfstring(argv);
        pthread_create(&id,NULL, &syscall1,&t1);
        pthread_join(id,NULL);
}
void rmthread(char ** segment){
    if(segment[1]==NULL){
        printf("Missing Operand\n");
        return;
    }
    int force = 0,sucmes =0;
    if(strcmp(segment[1],"-f")==0 || strcmp(segment[1],"-f\n")==0 || (segment[2]!=NULL && (strcmp(segment[2],"-f")==0 || strcmp(segment[2],"-f\n")==0 ))){
        force = 1;
    }
    if(strcmp(segment[1],"-v")==0 || strcmp(segment[1],"-v\n")==0 || (segment[2]!=NULL && (strcmp(segment[2],"-v")==0 || strcmp(segment[2],"-v\n")==0 ))){
        sucmes = 1;
    }
    if(force+sucmes== 1 && segment[1][0]!='-'){
        printf("Please place all flags at the beginning!\n");
        return;
    }
    int pid = fork();
    if(pid<0){
        printf("Failed to fork!\n");
        return;
    }if(pid==0){
        char * fpath = concatString(_PROGRAM_DIRECTORY,"/");
        char* mkname = concatString(_PROGRAM_DIRECTORY,"/rm.o");
        char* pathfinal = concatString(fpath, echoMessage(segment,force+sucmes+1,' '));
        char* argv[3] = {mkname,pathfinal,NULL};
        char* env[1] = {NULL};
        execve(mkname,argv,env);
        printf("FAILED 1");
        return;
    }else{
        int status;
        wait(&status);
        if(status!=0){
            if(force==1){
                return;
            }else{
                printf("File does not exist!\n");
            }
        }else if(sucmes==1){
            printf("File deleted Successfully!\n");
        }
    }
}
void shell_loop(){
    while(1) {
        char * x = getPWD();
        printf("\033[0;31m<\033[0;36m%s\033[0;31m>\033[0m ",basename(x));
        free(x);
        char **segment = getInput();
        if(segment == NULL){continue;}
        int ptr = 0;
        char* s0 = delim(segment[0]);
        //char* s0 = segment[0];
        if (segment[0]==NULL) {}
        else if (strcmp(s0, "exit") == 0) {free(s0); break; }
        else if(strcmp(s0,"cd")==0){ changeDir(segment);}
        else if(strcmp(s0,"pwd")==0){
            char * cwd = getPWD();
            printf("%s\n",cwd);
            free(cwd);
        }
        else if(strcmp(s0,"echo")==0){ echo(segment);}
        else if(strcmp(s0,"mkdir")==0){mkdir1(segment);}
        else if(strcmp(s0,"date")==0){date(segment);}
        else if(strcmp(s0,"ls")==0){ls(segment);}
        else if(strcmp(s0,"rm")==0){rm(segment);}
        else if(strcmp(s0,"cat")==0){cat(segment);}
        else if(strcmp(s0,"cat&t")==0){ catthread(segment);}
        else if(strcmp(s0,"rm&t")==0){rmthread(segment);}
        else{printf("Segment[0] is %s!\n",segment[0]);printf("Command Not Found!\n");}
        free(s0);

    }
}
int main(int argc, char* argv[]){
    _PROGRAM_DIRECTORY = getPWD();
    shell_loop();

return 0;
}