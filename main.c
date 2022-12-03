#include "header.h"

char* extract(char *currentdirectory,char *originaldirectory)
{
    // char directoryset[SIZE];

    char *directoryset=(char *)malloc(SIZE*sizeof(char));
    int n=0,setflag=0;

    if (strcmp(originaldirectory,currentdirectory)==0)
    {
        directoryset="~";
    }
    else if(strcmp(originaldirectory,currentdirectory)>0)
    {
        // printf("%s\n\n",currentdirectory);
        // printf("%s\n\n",originaldirectory);

        strcpy(directoryset,currentdirectory);
    }
    else
    {

        // printf("%s\n\n",currentdirectory);
        // printf("%s\n\n",originaldirectory);

        int tracker=0;
        for (int i=0;i<strlen(originaldirectory);i++)
        {
            if(currentdirectory[i]==originaldirectory[i])
            {
                tracker++;
            }
            else
            {
                break;
            }
        }

        // printf("%d\n",tracker);

        char subdirectory[SIZE];


        if (tracker==strlen(originaldirectory))
        {
            memset(subdirectory,0,sizeof(subdirectory));
            for (int j=tracker;j<(strlen(currentdirectory));j++)
            {
                subdirectory[j-tracker]=currentdirectory[j];
            }

            sprintf(directoryset,"~%s",subdirectory);


        }
        else
        {
            strcpy(directoryset,currentdirectory);
        }
    }

    return directoryset;
}

char homee[SIZE];
char prevdir[SIZE];
int setstartflag=0;
int processcount=0;
int dirtrack=1;

int main()
{
    
    char currentdirectory[SIZE];
    char originaldirectory[SIZE];
    

    getcwd(originaldirectory, sizeof(originaldirectory));

    strcpy(homee,originaldirectory);

    char username[SIZE];

    getlogin_r(username, sizeof(username));

    char device[SIZE];

    gethostname(device, sizeof(device));

    char *line = NULL;
    // char line[500];

    history = malloc(20 * sizeof(char*));
    for (int i = 0; i < 20; i++)
    history[i] = malloc((SIZE) * sizeof(char));

    while(1)
    {
        char *directory,directoryfinal[SIZE];

        ssize_t linelength = 0;

        getcwd(currentdirectory,sizeof(currentdirectory));

        directory = extract(currentdirectory,originaldirectory);

        int status;
        for(int i=1;i<=processcount;i++)
        {
            pid_t return_pid = waitpid(processarray[i], &status, WNOHANG);
            if(return_pid==processarray[i])
            {
                printf("Process with pid %d exited\n",processarray[i]);
                // processcount--;
                // for(int j=i;j<processcount;j++)
                // {
                //     processarray[j]=processarray[j+1];
                // }
            }
        }
        

        if (timediff>1)
        {
            printf("<%s%s@%s%s:%s%s took %0.1fsecs%s> ",MAGENTA,username,device,NORMAL_COLOR,CYAN,directory,timediff,NORMAL_COLOR);
        }
        else
        {
            printf("<%s%s@%s%s:%s%s%s> ",MAGENTA,username,device,NORMAL_COLOR,CYAN,directory,NORMAL_COLOR);
        }

        



        // memset(directory,0,strlen(directory));

        getline(&line, &linelength, stdin);

        if (strcmp(line,"\n")==0)
        {
            continue;
        }
        
        // chdir("test");

        // printf("%s",line);
        tokenize(line);
    }

}