#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <ctype.h>
#define SIZE 500

#define NORMAL_COLOR  "\x1B[0m"
#define GREEN  "\x1B[32m"
#define BLUE  "\x1B[34m"
#define CYAN "\x1B[36m"
#define MAGENTA "\x1B[35m"

void foregroundprocess(char *args[SIZE],int wordcount);
void backgroundprocess(char *args[SIZE],int wordcount);

void tokenize(char *line);
void filepermissions(struct stat fs,char *file);
void printls(char *rightnow);
void printls_a(char *rightnow,int wordcount);
void printls_l(char *rightnow,int wordcount);
void printls_la(char *rightnow,int wordcount);
void discover(char *rightnow,int base);
void usecommand(char *commands, char *homee);

extern char homee[SIZE];

// extern char *history[20];

extern char **history;

extern int historycount;

extern int processcount;

extern double timediff;

extern char prevdir[SIZE];

extern int setstartflag;

extern int processarray[SIZE];

extern int dirtrack;

// strcpy(prevdir,homee);


