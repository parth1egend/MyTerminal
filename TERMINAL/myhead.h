#include <stdio.h>
#include <readline/history.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <libgen.h>
#include <ctype.h>



#define CNRM "\x1B[0m"
#define CRED "\x1B[31m"
#define CGRN "\x1B[32m"
#define CYEL "\x1B[33m"
#define CBLU "\x1B[34m"
#define CMAG "\x1B[35m"
#define CCYN "\x1B[36m"
#define CWHT "\x1B[37m"
#define RESET "\033[0m"

void trimLeadingandTrailing(char *s);
void myls(char*,char*);
int mymv(char*,char*);
int mycp(char*,char*);
int myps(char*,char*);
int mygrep(char*,char*);
char *removeBlanks(const char *str);