#include "header.h"

double timediff=0;

void foregroundprocess(char *args[SIZE],int wordcount)
{
    args[wordcount]=NULL;

    time_t start, end;
    double timetaken=0;
    pid_t p_id;
    int status;
    start = time(NULL);
    p_id = fork();
    
    if (p_id == 0)
    {
        if(execvp(args[0], args)==-1);
            printf("Command not found\n");
        exit(0);
    }
    else if (p_id > 0)
    {
        
        do
        {
            waitpid(p_id, &status, 0);
        } while (WIFEXITED(status) == 0);
        
    }
    end = time(NULL);

    timediff=difftime(end,start);
}