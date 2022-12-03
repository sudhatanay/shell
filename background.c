#include "header.h"


// void backgroundprocess(char *args[SIZE],int wordcount)
// {
    

//     pid_t p_id;
//     pid_t p_id_2;
//     pid_t p_id_store;
//     char proc_store[300];

//     strcpy(proc_store, args[0]);
//     int status;
//     wordcount--;

//     args[wordcount]=NULL;

//     processcount++;
//     p_id = fork();
//     if (p_id == 0)
//     {

//         execvp(args[0], args);

//         exit(0);
//     }
//     else if (p_id > 0)
//     {
//         printf("[%d] %d\n", processcount,p_id);

//         p_id_2 = fork();
//         if (p_id_2 == 0)
//         {
//             /* continue */
//         }
//         else if (p_id_2 > 0)
//         {

//             do
//             {
//                 waitpid(p_id, &status, 0);

//             } while (WIFEXITED(status) == 0);
//             printf("%s with pid %d exited\n", proc_store, p_id);
//             do
//             {
//                 waitpid(p_id_2, &status, 0);
//             } while (WIFEXITED(status) == 0);
//         }
//     }
// }

int processarray[SIZE];

void backgroundprocess(char *args[SIZE],int wordcount)
{
    args[wordcount]=NULL;

    time_t start, end;
    double timetaken=0;
    pid_t p_id;
    int status;
    processcount++;
    wordcount--;

    p_id = fork();
    processarray[processcount]=p_id;
    // printf("%d\n",processarray[processcount]);
    
    if (p_id == 0)
    {
        setpgid(0, 0);
        if(execvp(args[0], args)==-1);
            printf("Command not found\n");
        exit(0);
    }
    else if (p_id > 0)
    {
        printf("[%d] %d process created\n",processcount,p_id);
        // do
        // {
        //     waitpid(p_id, &status, 0);
        // } while (WIFEXITED(status) == 0);
        
    }

}