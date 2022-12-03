#include "header.h"

// char prevdir[SIZE];
// int setstartflag=0;

void tokenize(char *line)
{
    char linebackup[SIZE];
    char lineusage[SIZE];

    strcpy(linebackup,line);
    char *commands;
    int commandcount=0;

    commands=strtok(line,";\n");
    // commandcount++;

    while(commands!=NULL)
    {
        commands=strtok(NULL,";\n");
        commandcount++;
    }

    // printf("%d\n",commandcount);
    strcpy(lineusage,linebackup);
    commands=strtok(lineusage,";\n");

    usecommand(commands,homee);
    commandcount--;

    if (setstartflag==0)
    {
        strcpy(prevdir,homee);
        setstartflag=1;
    }

    // printf("%s\n",prevdir);

    while(commandcount>0)
    {
        strcpy(lineusage,linebackup);
        commands=strtok(lineusage,";\n");
        for (int i=0;i<commandcount;i++)
        {
            commands=strtok(NULL,";\n");
            usecommand(commands,homee);
            commandcount--;
        }
    }

}