#include "header.h"

int historycount=0;
char **history;

void usecommand(char *commands,char* homee)
{

    // printf("%s\n",commands);
    int wordcount=0;
    char *args[SIZE];
    char *words,*commandreset,*fgbgcheck,wordsbackup[SIZE],*tester,*countwordsstorage, directory[SIZE],backupcommands[SIZE],wordcountbackup[SIZE],prevdirbackup[SIZE],*prevdirstorage;
    // char prevdir[SIZE];
    char prevcommand[SIZE];
    
    // if (setstartflag==0)
    // {
    //     strcpy(prevdir,homee);
    //     setstartflag=1;
    // }

    // getcwd(prevdir,sizeof(prevdir));
    strcpy(backupcommands,commands);
    strcpy(wordcountbackup,commands);
    strcpy(prevdirbackup,commands);


    FILE *fp;
    fp=fopen("history.txt","a");
    if (setstartflag==0)
    {
        strcpy(prevcommand,commands);
        fprintf(fp,"%s\n",commands);
        setstartflag=1;
        historycount++;
    }
    fclose(fp);
    
    countwordsstorage=strtok(wordcountbackup," \n\t");
    args[wordcount]=countwordsstorage;
    // printf("TEST\n");
    while(countwordsstorage!=NULL)
    {
        countwordsstorage=strtok(NULL," \n\t");
        wordcount++;
        args[wordcount]=countwordsstorage;
    }

    
    FILE *fp2;
    fp2=fopen("history.txt","a");
    if(strcmp(prevcommand,commands)!=0)
    {
        fprintf(fp2,"%s\n",commands);
        strcpy(prevcommand,commands);
        historycount++;
    }
    fclose(fp2);

    char commandscopy[SIZE];
    strcpy(commandscopy,backupcommands);

    words=strtok(commandscopy," \n\t");
    int flag=0;

    if (strcmp(words,"cd")==0)
    {
        
        // printf("%d\n",wordcount);


        // printf("%s\n",prevdir);

        if (wordcount==1)
        {
            chdir(homee);
            // strcpy(prevdir,homee);
            return;
        }
        else if(wordcount>2)
        {
            printf("Error: Too many arguments passed\n");
            return;
        }
        
        words=strtok(NULL," \n\t");

        if(strcmp(words,"-")==0)
        {
            char prevdirscam[SIZE];
            getcwd(prevdirscam,sizeof(prevdirscam));
            printf("%s\n",prevdir);
            chdir(prevdir);
            strcpy(prevdir,prevdirscam);
            return;
        }

        getcwd(prevdir,sizeof(prevdir));

        strcpy(wordsbackup,words);
        // printf("%s\n",wordsbackup);

        if (wordsbackup[0]=='~')
        {
            tester=strtok(wordsbackup,"/");

            if(strcmp(tester,"~")==0)
            {
                strcpy(wordsbackup,words);
                tester=strtok(wordsbackup,"/ \n");
                tester=strtok(NULL," \n");
                chdir(homee);
                chdir(tester);
                return;
            }
        }



        words=strtok(prevdirbackup," \n\t");
        words=strtok(NULL," \n\t");
        // if(strcmp(words,"/")==0)
        // {
        //     chdir("/");
        //     return;
        // }
        chdir(words);
        return;

    }
    else if (strcmp(words,"pwd")==0)
    {
        if (wordcount==1)
        {
            printf("%s\n",getcwd(directory,sizeof(directory)));
            return;
        }
        else if(wordcount>1)
        {
            printf("Error: Too many arguments passed\n");
            return;
        }
    }
    else if (strcmp(words,"echo")==0)
    {
        if (wordcount==1)
        {
            printf("\n");
            return;
        }
        else
        {
            for (int i=0;i<wordcount-1;i++)
            {
                    words=strtok(NULL," \t\n");
                    printf("%s ",words);
            }
            printf("\n");
        }

    }
    else if (strcmp(words,"ls")==0)
    {
        // printf("%d\n",wordcount);
        char rightnow[SIZE];
        int lflag=0;
        int aflag=0;
        while(words=strtok(NULL," \t\n"))
        {
            // printf("%s\n",words);
            if (strcmp(words,"-a")==0)
            {
                aflag++;
            }
            else if (strcmp(words,"-l")==0)
            {
                lflag++;
            }
            else if (strcmp(words,"-al")==0 || strcmp(words,"-la")==0)
            {
                aflag++;
                lflag++;
            }
        }

        // printf("%d %d\n",aflag,lflag);

        char stringbackup[SIZE];
        int filecount=0;
        strcpy(stringbackup,backupcommands);
        words=strtok(stringbackup," \t\n");

        while(words=strtok(NULL," \t\n"))
        {
            if (strcmp(words,"-a")==0 || strcmp(words,"-l")==0 || strcmp(words,"-al")==0 || strcmp(words,"-la")==0)
            {
                continue;
            }
            else
            {
                filecount++;
            }
        }

        strcpy(stringbackup,backupcommands);
        words=strtok(stringbackup," \t\n");

        if (filecount==0)
        {
            // printf("TEST\n");
            getcwd(rightnow,sizeof(rightnow));
            if (lflag>0 && aflag>0)
            {
                // printf("%s:\n",words);
                printls_la(rightnow,filecount);
                printf("\n");
            }
            else if (lflag>0)
            {
                printls_l(rightnow,filecount);
                printf("\n");
            }
            else if (aflag>0)
            {
                printls_a(rightnow,filecount);
                printf("\n");
            }
            else
            {
                printls(rightnow);
                printf("\n");
            }
        }

        while(words=strtok(NULL," \t\n"))
        {
            if (strcmp(words,"-a")==0 || strcmp(words,"-l")==0 || strcmp(words,"-al")==0 || strcmp(words,"-la")==0)
            {
                continue;
            }
            else
            {
                if (filecount==1 && strcmp(words,"~")==0)
                {
                    // printf("TEST\n");
                    getcwd(rightnow,sizeof(rightnow));
                    if (lflag>0 && aflag>0)
                    {
                        // printf("%s:\n",words);
                        printls_la(rightnow,filecount);
                        printf("\n");
                    }
                    else if (lflag>0)
                    {
                        printls_l(rightnow,filecount);
                        printf("\n");
                    }
                    else if (aflag>0)
                    {
                        printls_a(rightnow,filecount);
                        printf("\n");
                    }
                    else
                    {
                        printls(rightnow);
                        printf("\n");
                    }
                }
                else if (filecount==1 && strcmp(words,"-")==0)
                {
                    // printf("TEST\n");
                    strcpy(rightnow,prevdir);
                    if (lflag>0 && aflag>0)
                    {
                        // printf("%s:\n",words);
                        printls_la(rightnow,filecount);
                        printf("\n");
                    }
                    else if (lflag>0)
                    {
                        printls_l(rightnow,filecount);
                        printf("\n");
                    }
                    else if (aflag>0)
                    {
                        printls_a(rightnow,filecount);
                        printf("\n");
                    }
                    else
                    {
                        printls(rightnow);
                        printf("\n");
                    }
                }
                else
                {
                    DIR * d=opendir(words);
                    if(d==NULL)
                    {
                        struct stat filetype;
                        int x=stat(words,&filetype);
                        if (S_ISREG(filetype.st_mode))
                        {
                            if (lflag>0 && aflag>0)
                            {
                                printf("%s:\n",words);
                                struct stat fs;
                                filepermissions(fs,words);
                                printf("%s\n",words);
                                printf("\n");
                                
                            }
                            else if (lflag>0)
                            {
                                struct stat fs;
                                filepermissions(fs,words);
                                printf("%s\n",words);
                                printf("\n");
                                
                            }
                            else
                            {
                                printf("%s\n",words);
                                printf("\n");
                            }
                        }
                        else
                        {
                            printf("%s: No such file or directory\n",words);
                            printf("\n");
                        }
                    }
                    else
                    {
                        if (lflag>0 && aflag>0)
                        {
                            printf("%s:\n",words);
                            strcpy(rightnow,words);
                            printls_la(rightnow,filecount);
                            printf("\n");
                        }
                        else if (lflag>0)
                        {
                            strcpy(rightnow,words);
                            printls_l(rightnow,filecount);
                            printf("\n");
                        }
                        else if (aflag>0)
                        {
                            strcpy(rightnow,words);
                            printls_a(rightnow,filecount);
                            printf("\n");
                        }
                        else
                        {
                            strcpy(rightnow,words);
                            printls(rightnow);
                            printf("\n");
                        }
                    }
                }

                
                // closedir(d);
            }
        }
    }
    else if (strcmp(words, "pinfo")==0)
    {
        pid_t p_id;
        int id_num;
        if (wordcount == 1)
        {
            p_id = getpid();
        }
        else if (wordcount == 2)
        {
            id_num = atoi(args[1]);
            p_id = id_num;
        }

        char filestring[300];
        char filestring_2[300];
        char filestring_3[300];
        char *split, *split_2, *split_3;
        int i = 0;
        char *kb, *kb_2;
        printf("pid -- %d\n", p_id);
        char pro_stat_path[300];
        sprintf(pro_stat_path, "/proc/%d/status", p_id);
        FILE *fp = fopen(pro_stat_path, "r");

        while (fgets(filestring_3, sizeof(filestring_3), (FILE *)fp) != NULL)
        {
            if (strncmp("Name:", filestring_3, strlen("Name")) == 0)
                break;
        }

        split_3 = strtok(filestring_3, ": ");
        split_3 = strtok(NULL, ": ");

        while (fgets(filestring, sizeof(filestring), (FILE *)fp) != NULL)
        {
            if (strncmp("State:", filestring, strlen("State")) == 0)
                break;
        }
        /*for (i = 0; i < strlen(filestring); i++)
        {
            printf("%d %c\n", i, filestring[i]);
        }*/
        split = strtok(filestring, ": \n");
        split = strtok(NULL, " \n");

        while (fgets(filestring_2, sizeof(filestring_2), (FILE *)fp) != NULL)
        {
            if (strncmp("VmRSS:", filestring_2, strlen("VmRSS")) == 0)
                break;
        }

        split_2 = strtok(filestring_2, " \n");
        split_2 = strtok(NULL, " \n");
        printf("Process Status -- %s\n", split);
        printf("memory -- %s kB\n", split_2);
        printf("Executable Path -- %s\n", split_3);
    }
    else if (strcmp("exit",words)==0)
    {
        exit(0);
    }
    else if (strcmp(words,"history")==0)
    {
        char ch = 0;
        long num_lines = 0;
        int lineoutput=10;

        fp=fopen("history.txt","r");

        while(!feof(fp))
        {
            ch = fgetc(fp);
            if(ch == '\n')
            {
                num_lines++;
            }
        }
        fseek(fp, 0, SEEK_SET);

        const int length = 100;
        char line[length];
        char *c = 0;
        long line_count = 0;

        if(lineoutput > num_lines)
        {
        lineoutput = num_lines;
        }

        do
        {
            c = fgets(line, length, fp);
            if (c != NULL && (line_count >= num_lines - lineoutput))
            {
                printf("%s", line);            
            }
            line_count++;
        }while (c != NULL);
        
    }
    else if (strcmp(words,"discover")==0)
    {
        if (wordcount==2)
        {
            discover(args[1],0);
        }
        else
        {
            discover(homee,0);
        }

    }
    else if (strcmp("&", args[wordcount-1]) == 0)
    {
        args[wordcount-1] = NULL;
        backgroundprocess(args,wordcount);
    }
    else
    {
        foregroundprocess(args,wordcount);
    }
}