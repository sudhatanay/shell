#include "header.h"

int blocksize(struct stat fs, char *file)
{
    stat(file,&fs);
    int blocks=0;
    blocks=fs.st_blocks;
    return blocks;
}

void filepermissions(struct stat fs,char *file)
{
    int x=stat(file,&fs);

    printf("%s",(S_ISDIR(fs.st_mode))?"d":"-");
    printf("%s",(fs.st_mode & S_IRUSR)?"r":"-");
    printf("%s",(fs.st_mode & S_IWUSR)?"w":"-");
    printf("%s",(fs.st_mode & S_IXUSR)?"x":"-");
    printf("%s",(fs.st_mode & S_IRGRP)?"r":"-");
    printf("%s",(fs.st_mode & S_IWGRP)?"w":"-");
    printf("%s",(fs.st_mode & S_IXGRP)?"x":"-");
    printf("%s",(fs.st_mode & S_IROTH)?"r":"-");
    printf("%s",(fs.st_mode & S_IWOTH)?"w":"-");
    printf("%s ",(fs.st_mode & S_IXOTH)?"x":"-");

    printf("%ld ",fs.st_nlink);

    struct passwd *pw = getpwuid(fs.st_uid);
    struct group  *gr = getgrgid(fs.st_gid);
    struct tm *timeinfo=localtime(&fs.st_mtime);

    printf("%s %s ",pw ->pw_name,gr ->gr_name);

    printf("%7ld ",(fs.st_size));

    char month[10];

    switch(timeinfo->tm_mon)
    {
        case 0:
            sprintf(month,"Jan");
            break;
        case 1:
            sprintf(month,"Feb");
            break;
        case 2:
            sprintf(month,"Mar");
            break;
        case 3:
            sprintf(month,"Apr");
            break;
        case 4:
            sprintf(month,"May");
            break;
        case 5:
            sprintf(month,"Jun");
            break;
        case 6:
            sprintf(month,"Jul");
            break;
        case 7:
            sprintf(month,"Aug");
            break;
        case 8:
            sprintf(month,"Sep");
            break;
        case 9:
            sprintf(month,"Oct");
            break;
        case 10:
            sprintf(month,"Nov");
            break;
        case 11:
            sprintf(month,"Dec");
            break;
    }

    printf("%s %.2d %.2d:%.2d ",month,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min);
}

// void printls(char *rightnow)
// {
//     DIR * d=opendir(rightnow);
//     struct dirent * directoryentity;
//     struct stat directoryentityinfo;
//     while ((directoryentity=readdir(d))!= NULL)
//     {
//         if(directoryentity -> d_type != DT_DIR)
//         {
//             if(stat(directoryentity -> d_name, &directoryentityinfo) == 0 && directoryentityinfo.st_mode & S_IXUSR)
//             {
//                 printf("%s%-1s%s\t",GREEN,directoryentity -> d_name,NORMAL_COLOR);
//             }
//             else
//             {
//                 printf("%-1s\t",directoryentity -> d_name);
//             }
//         }
//         else if (directoryentity -> d_type == DT_DIR && directoryentity -> d_name[0] != '.')
//         {
//             printf("%s%-1s%s\t",BLUE,directoryentity -> d_name,NORMAL_COLOR);
//         }
//     }
//     printf("\n");
// }

void printls(char *rightnow)
{
    DIR * d=opendir(rightnow);
    struct dirent ** directorylist;
    struct stat directoryentityinfo;

    int n;

    n= scandir(rightnow,&directorylist,NULL,alphasort);

    for (int i=0;i<n;i++)
    {
        if(directorylist[i] -> d_type != DT_DIR)
        {
            if(stat(directorylist[i] -> d_name, &directoryentityinfo) == 0 && directoryentityinfo.st_mode & S_IXUSR)
            {
                printf("%s%s%s\n",GREEN,directorylist[i] -> d_name,NORMAL_COLOR);
            }
            else
            {
                printf("%s\n",directorylist[i] -> d_name);
            }
        }
        else if (directorylist[i] -> d_type == DT_DIR && directorylist[i] -> d_name[0] != '.')
        {
            printf("%s%s%s\n",BLUE,directorylist[i] -> d_name,NORMAL_COLOR);
        }
    }
    // while ((directoryentity=readdir(d))!= NULL)
    // {
        
    // }
    printf("\n");
}

// void printls_l(char *rightnow)
// {
//     DIR * d=opendir(rightnow);
//     struct dirent * directoryentity;
//     struct stat directoryentityinfo;
//     while ((directoryentity=readdir(d))!= NULL)
//     {
//         if(directoryentity -> d_type != DT_DIR)
//         {
//             if(stat(directoryentity -> d_name, &directoryentityinfo) == 0 && directoryentityinfo.st_mode & S_IXUSR)
//             {
//                 filepermissions(directoryentityinfo,directoryentity -> d_name);
//                 printf("%s%-1s%s\t\n",GREEN,directoryentity -> d_name,NORMAL_COLOR);
//             }
//             else
//             {
//                 filepermissions(directoryentityinfo,directoryentity -> d_name);
//                 printf("%-1s\t\n",directoryentity -> d_name);
//             }
//         }
//         else if (directoryentity -> d_type == DT_DIR && directoryentity -> d_name[0] != '.')
//         {
//             filepermissions(directoryentityinfo,directoryentity -> d_name);
//             printf("%s%-1s%s\t\n",BLUE,directoryentity -> d_name,NORMAL_COLOR);
//         }
//     }
//     printf("\n");
// }

void printls_l(char *rightnow,int wordcount)
{
    DIR * d=opendir(rightnow);
    struct dirent ** directorylist;
    struct stat directoryentityinfo;

    char rightnowbackup[SIZE];
    strcpy(rightnowbackup,rightnow);

    int blockttotal=0;
    int blockvalue;

    int n;

    n= scandir(rightnow,&directorylist,NULL,alphasort);

    for (int i=0;i<n;i++)
    {
        if(directorylist[i] -> d_type != DT_DIR)
        {
            if(stat(directorylist[i] -> d_name, &directoryentityinfo) == 0 && directoryentityinfo.st_mode & S_IXUSR)
            {
                if (wordcount==0)
                {
                    blockvalue=blocksize(directoryentityinfo,directorylist[i] -> d_name);
                    blockttotal+=blockvalue;
                }
                else
                {
                    strcat(rightnowbackup,"/");
                    strcat(rightnowbackup,directorylist[i]->d_name);
                    // filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                    blockvalue=blocksize(directoryentityinfo,rightnowbackup);
                    blockttotal+=blockvalue;
                    strcpy(rightnowbackup,rightnow);
                }

            }
            else
            {
                if (wordcount==0)
                {
                    blockvalue=blocksize(directoryentityinfo,directorylist[i] -> d_name);
                    blockttotal+=blockvalue;
                }
                else
                {
                    strcat(rightnowbackup,"/");
                    strcat(rightnowbackup,directorylist[i]->d_name);
                    // filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                    blockvalue=blocksize(directoryentityinfo,rightnowbackup);
                    blockttotal+=blockvalue;
                    strcpy(rightnowbackup,rightnow);
                }
            }
        }
        else if (directorylist[i] -> d_type == DT_DIR && directorylist[i] -> d_name[0] != '.')
        {
            if (wordcount==0)
            {
                blockvalue=blocksize(directoryentityinfo,directorylist[i] -> d_name);
                blockttotal+=blockvalue;
            }
            else
            {
                strcat(rightnowbackup,"/");
                strcat(rightnowbackup,directorylist[i]->d_name);
                // filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                blockvalue=blocksize(directoryentityinfo,rightnowbackup);
                blockttotal+=blockvalue;
                strcpy(rightnowbackup,rightnow);
            }
        }
    }

    printf("total %d\n",blockttotal/2);

    n= scandir(rightnow,&directorylist,NULL,alphasort);

    for (int i=0;i<n;i++)
    {
        if(directorylist[i] -> d_type != DT_DIR)
        {
            if(stat(directorylist[i] -> d_name, &directoryentityinfo) == 0 && directoryentityinfo.st_mode & S_IXUSR)
            {
                if (wordcount==0)
                {
                    filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                    printf("%s%-1s%s\t\n",GREEN,directorylist[i] -> d_name,NORMAL_COLOR);
                }
                else
                {
                    strcat(rightnowbackup,"/");
                    strcat(rightnowbackup,directorylist[i]->d_name);
                    // filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                    filepermissions(directoryentityinfo,rightnowbackup);
                    strcpy(rightnowbackup,rightnow);
                    printf("%s%-1s%s\t\n",GREEN,directorylist[i] -> d_name,NORMAL_COLOR);
                }

            }
            else
            {
                if (wordcount==0)
                {
                    filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                    printf("%-1s\t\n",directorylist[i] -> d_name);
                }
                else
                {
                    strcat(rightnowbackup,"/");
                    strcat(rightnowbackup,directorylist[i]->d_name);
                    // filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                    filepermissions(directoryentityinfo,rightnowbackup);
                    strcpy(rightnowbackup,rightnow);
                    printf("%-1s\t\n",directorylist[i] -> d_name);
                }
            }
        }
        else if (directorylist[i] -> d_type == DT_DIR && directorylist[i] -> d_name[0] != '.')
        {
            if (wordcount==0)
            {
                filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                printf("%s%-1s%s\t\n",BLUE,directorylist[i] -> d_name,NORMAL_COLOR);
            }
            else
            {
                strcat(rightnowbackup,"/");
                strcat(rightnowbackup,directorylist[i]->d_name);
                // filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                filepermissions(directoryentityinfo,rightnowbackup);
                strcpy(rightnowbackup,rightnow);
                printf("%s%-1s%s\t\n",BLUE,directorylist[i] -> d_name,NORMAL_COLOR);
            }
        }
    }
    printf("\n");
}

// void printls_a(char *rightnow)
// {
//     DIR * d=opendir(rightnow);
//     struct dirent * directoryentity;
//     struct stat directoryentityinfo;
//     while ((directoryentity=readdir(d))!= NULL)
//     {
//         if(directoryentity -> d_type != DT_DIR)
//         {
//             if(stat(directoryentity -> d_name, &directoryentityinfo) == 0 && directoryentityinfo.st_mode & S_IXUSR)
//             {
//                 printf("%s%-1s%s\t",GREEN,directoryentity -> d_name,NORMAL_COLOR);
//             }
//             else
//             {
//                 printf("%-1s\t",directoryentity -> d_name);
//             }
//         }
//         else if (directoryentity -> d_type == DT_DIR)
//         {
//             printf("%s%-1s%s\t",BLUE,directoryentity -> d_name,NORMAL_COLOR);
//         }
//     }
//     printf("\n");
// }

void printls_a(char *rightnow,int wordcount)
{
    DIR * d=opendir(rightnow);
    struct dirent ** directorylist;
    struct stat directoryentityinfo;

    int n;

    n= scandir(rightnow,&directorylist,NULL,alphasort);

    for (int i=0;i<n;i++)
    {
        if(directorylist[i] -> d_type != DT_DIR)
        {
            if(stat(directorylist[i] -> d_name, &directoryentityinfo) == 0 && directoryentityinfo.st_mode & S_IXUSR)
            {
                printf("%s%s%s\n",GREEN,directorylist[i] -> d_name,NORMAL_COLOR);
            }
            else
            {
                printf("%s\n",directorylist[i] -> d_name);
            }
        }
        else if (directorylist[i] -> d_type == DT_DIR)
        {
            printf("%s%s%s\n",BLUE,directorylist[i] -> d_name,NORMAL_COLOR);
        }
    }
    // while ((directoryentity=readdir(d))!= NULL)
    // {
        
    // }
    printf("\n");
}

// void printls_la(char *rightnow)
// {
//     DIR * d=opendir(rightnow);
//     struct dirent * directoryentity;
//     struct stat directoryentityinfo;
//     while ((directoryentity=readdir(d))!= NULL)
//     {
//         if(directoryentity -> d_type != DT_DIR)
//         {
//             if(stat(directoryentity -> d_name, &directoryentityinfo) == 0 && directoryentityinfo.st_mode & S_IXUSR)
//             {
//                 filepermissions(directoryentityinfo,directoryentity -> d_name);
//                 printf("%s%-1s%s\t\n",GREEN,directoryentity -> d_name,NORMAL_COLOR);
//             }
//             else
//             {
//                 filepermissions(directoryentityinfo,directoryentity -> d_name);
//                 printf("%-1s\t\n",directoryentity -> d_name);
//             }
//         }
//         else if (directoryentity -> d_type == DT_DIR)
//         {
//             filepermissions(directoryentityinfo,directoryentity -> d_name);
//             printf("%s%-1s%s\t\n",BLUE,directoryentity -> d_name,NORMAL_COLOR);
//         }
//     }
//     printf("\n");
// }

void printls_la(char *rightnow,int wordcount)
{
    DIR * d=opendir(rightnow);
    struct dirent ** directorylist;
    struct stat directoryentityinfo;

    char rightnowbackup[SIZE];
    strcpy(rightnowbackup,rightnow);

    int blockttotal=0;
    int blockvalue;

    int n;

    n= scandir(rightnow,&directorylist,NULL,alphasort);

    for (int i=0;i<n;i++)
    {
        if(directorylist[i] -> d_type != DT_DIR)
        {
            if(stat(directorylist[i] -> d_name, &directoryentityinfo) == 0 && directoryentityinfo.st_mode & S_IXUSR)
            {
                if (wordcount==0)
                {
                    blockvalue=blocksize(directoryentityinfo,directorylist[i] -> d_name);
                    blockttotal+=blockvalue;
                }
                else
                {
                    strcat(rightnowbackup,"/");
                    strcat(rightnowbackup,directorylist[i]->d_name);
                    // filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                    blockvalue=blocksize(directoryentityinfo,rightnowbackup);
                    blockttotal+=blockvalue;
                    strcpy(rightnowbackup,rightnow);
                }

            }
            else
            {
                if (wordcount==0)
                {
                    blockvalue=blocksize(directoryentityinfo,directorylist[i] -> d_name);
                    blockttotal+=blockvalue;
                }
                else
                {
                    strcat(rightnowbackup,"/");
                    strcat(rightnowbackup,directorylist[i]->d_name);
                    // filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                    blockvalue=blocksize(directoryentityinfo,rightnowbackup);
                    blockttotal+=blockvalue;
                    strcpy(rightnowbackup,rightnow);
                }
            }
        }
        else if (directorylist[i] -> d_type == DT_DIR)
        {
            if (wordcount==0)
            {
                blockvalue=blocksize(directoryentityinfo,directorylist[i] -> d_name);
                blockttotal+=blockvalue;
            }
            else
            {
                strcat(rightnowbackup,"/");
                strcat(rightnowbackup,directorylist[i]->d_name);
                // filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                blockvalue=blocksize(directoryentityinfo,rightnowbackup);
                blockttotal+=blockvalue;
                strcpy(rightnowbackup,rightnow);
            }
        }
    }

    printf("total %d\n",blockttotal/2);

    n= scandir(rightnow,&directorylist,NULL,alphasort);

    for (int i=0;i<n;i++)
    {
        if(directorylist[i] -> d_type != DT_DIR)
        {
            if(stat(directorylist[i] -> d_name, &directoryentityinfo) == 0 && directoryentityinfo.st_mode & S_IXUSR)
            {
                if (wordcount==0)
                {
                    filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                    printf("%s%-1s%s\t\n",GREEN,directorylist[i] -> d_name,NORMAL_COLOR);
                }
                else
                {
                    strcat(rightnowbackup,"/");
                    strcat(rightnowbackup,directorylist[i]->d_name);
                    // filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                    filepermissions(directoryentityinfo,rightnowbackup);
                    strcpy(rightnowbackup,rightnow);
                    printf("%s%-1s%s\t\n",GREEN,directorylist[i] -> d_name,NORMAL_COLOR);
                }

            }
            else
            {
                if (wordcount==0)
                {
                    filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                    printf("%-1s\t\n",directorylist[i] -> d_name);
                }
                else
                {
                    strcat(rightnowbackup,"/");
                    strcat(rightnowbackup,directorylist[i]->d_name);
                    // filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                    filepermissions(directoryentityinfo,rightnowbackup);
                    strcpy(rightnowbackup,rightnow);
                    printf("%-1s\t\n",directorylist[i] -> d_name);
                }
            }
        }
        else if (directorylist[i] -> d_type == DT_DIR)
        {
            if (wordcount==0)
            {
                filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                printf("%s%-1s%s\t\n",BLUE,directorylist[i] -> d_name,NORMAL_COLOR);
            }
            else
            {
                strcat(rightnowbackup,"/");
                strcat(rightnowbackup,directorylist[i]->d_name);
                // filepermissions(directoryentityinfo,directorylist[i] -> d_name);
                filepermissions(directoryentityinfo,rightnowbackup);
                strcpy(rightnowbackup,rightnow);
                printf("%s%-1s%s\t\n",BLUE,directorylist[i] -> d_name,NORMAL_COLOR);
            }
        }
    }
    printf("\n");
}


void discover(char *rightnow,int base)
{
    int i;
        char path[1000];
        char initializedir[SIZE];
        struct dirent *dp;
        DIR *dir = opendir(rightnow);

        if (!dir)
            return;

        while ((dp = readdir(dir)) != NULL)
        {
            if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
            {
                for (i=0; i<base; i++) 
                {
                    if (i%2 == 0 || i == 0)
                        printf("%s", " - ");
                    else
                        printf(" ");
                }

                printf("%s\n", dp->d_name);
                

                strcpy(path, rightnow);
                strcat(path, "/");
                strcat(path, dp->d_name);
                discover(path, base + 2);
            }
        }

        closedir(dir);
}