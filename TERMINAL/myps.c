#include "myhead.h"

int allnumbers(char *name)
{
    int k = 1;
    for (int i = 0; i < strlen(name); i++)
    {
        if (!isdigit(name[i]))
        {
            k = 0;
        }
    }
    return k;
}

struct data
{
    int pid;
    int ppid;
    int sid;
    char cmd[1000];
    unsigned long long int rss;
    long int sz;
    int uid;
    char username[256];
    int psr;
    char tty_name[256];
    long long int utime;
    long long int stime;
    time_t STIME;

    char formed_utime[256];
    char formed_STIME[256];
    int c;
};

int myps(char *command, char *pwd)
{
    char *newcommand = removeBlanks(command);
    char *cmdarray[100];
    int i = 0, n = 0, v = 0;
    int k = 0;
    cmdarray[k] = strtok(newcommand, " ");
    while (cmdarray[k] != NULL)
        cmdarray[++k] = strtok(NULL, " ");

    int a = 0, e = 0, f = 0;

    if(k>2)
    {
        printf("error:Invalid command\n");
        return 0;
    }

    if (k == 2)
    {
        for (int i = 1; cmdarray[1][i] != '\0'; i++)
        {
            if (cmdarray[1][i] == 'a')
            {
                a = 1;
            }
            else if (cmdarray[1][i] == 'e')
            {
                e = 1;
            }
            else if (cmdarray[1][i] == 'f')
            {
                f = 1;
            }
            else if (cmdarray[1][i] == '\0')
            {
                break;
            }
            else if (cmdarray[1][i] == ' ')
            {
                break;
            }
            else
            {
                printf("error: command not found\n");
                return 0;
            }
        }
    }

    int hid = getpid();
    int ppid = getppid();
    char curtty[256];
    memset(curtty, '\0', 256);
    char new1[256];
    memset(new1, '\0', 256);
    sprintf(new1, "/proc/%d/fd/0", hid);
    int fd = open(new1, O_RDONLY, 0);
    strcpy(curtty, ttyname(fd));
    close(fd);
    memset(new1, '\0', 256);
    strcpy(new1, curtty);
    memset(curtty, '\0', 256);
    for (int i = 5; i < strlen(new1); i++)
    {
        curtty[i - 5] = new1[i];
    }

    DIR *dir;
    struct dirent *dir_entry;

    dir = opendir("/proc");

    if (dir == NULL)
    {
        printf("Error opening /proc directory\n");
        return 0;
    }
    // if f is false
    // printf("%5s\t\t%10s\t\t%9s\t\tCMD\n" ,"PID" , "TTY" , "TIME");

    // if f is true
    if (f == 0)
    {
        printf("%5s\t\t%10s\t\t%9s\t\tCMD\n", "PID", "TTY", "TIME");
    }

    if (f == 1 && (a==1 || e==1))
    {
        printf("%-15s\t%5s\t%5s\t%s %5s %-5s\t%9s\t%s\n", "UID", "PID", "PPID", "C", "STIME", "TTY", "TIME", "CMD");
    }

    while ((dir_entry = readdir(dir)) != NULL)
    {

        if (allnumbers(dir_entry->d_name))
        {
            struct data property;
            char address[1000];
            sprintf(address, "/proc/%s/stat", dir_entry->d_name);
            FILE *file = fopen(address, "r");
            fscanf(file, "%d %s %*c %d %*d %d %*d %*d %*u %*d %*d %*d %*d %lld %lld %*lld %*lld %*d %*d %*d %*d %ld %*d %*llu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %d %d",
                   &property.pid, property.cmd, &property.ppid, &property.sid, &property.utime, &property.stime, &property.STIME, &property.psr, &property.c);
            property.c = property.stime / sysconf(_SC_CLK_TCK);
            fclose(file);
            sprintf(address, "/proc/%s/statm", dir_entry->d_name);
            file = fopen(address, "r");
            fscanf(file, "%ld %llu", &property.sz, &property.rss);
            property.rss *= 4;
            fclose(file);
            sprintf(address, "/proc/%s/status", dir_entry->d_name);
            file = fopen(address, "r");
            char line[256];
            while (fgets(line, sizeof(line), file))
            {
                if (sscanf(line, "Uid:\t%d", &property.uid) == 1)
                {
                    break;
                }
            }
            fclose(file);
            struct passwd *pw = malloc(sizeof(struct passwd));
            pw = getpwuid(property.uid);
            strcpy(property.username, pw->pw_name);
            sprintf(address, "/proc/%s/fd/0", dir_entry->d_name);
            int fd = open(address, O_RDONLY, 0);
            if (ttyname(fd) != NULL)
                strcpy(property.tty_name, ttyname(fd));
            else
                strcpy(property.tty_name, "?");
            close(fd);

            time_t uptime;
            file = fopen("/proc/uptime", "r");
            fscanf(file, "%ld", &uptime);
            fclose(file);
            property.STIME = (uptime - (property.STIME) / sysconf(_SC_CLK_TCK));

            long long int PROG = (property.utime + property.stime) / sysconf(_SC_CLK_TCK);
            snprintf(property.formed_utime, 9, "%.02lld:%.02lld:%.02lld", (PROG / 3600) % 3600, (PROG / 60) % 60, PROG % 60);
            char new[1000];
            memset(new, '\0', 256);
            strcpy(new, property.cmd);
            for (int i = 1; i < strlen(new) - 1; i++)
            {
                property.cmd[i - 1] = new[i];
                property.cmd[i] = '\0';
            }
            if (property.tty_name[0] != '?')
            {
                memset(new, '\0', 256);
                strcpy(new, property.tty_name);
                memset(property.tty_name, '\0', 256);
                for (int i = 5; i < strlen(new); i++)
                {
                    property.tty_name[i - 5] = new[i];
                }
            }

            time_t now = time(0);
            property.STIME = now - property.STIME;
            struct tm *loop = localtime(&property.STIME);
            strftime(property.formed_STIME, 256, "%H:%M", loop);
            /// if only e is true
            // printf("%4d\t\t%10s\t\t%9s\t\t%s\n", property.pid, property.tty_name, property.formed_utime, property.cmd);

            /// if nothing is true
            // if(!strcmp(property.tty_name , curtty))
            // printf("%4d\t\t%10s\t\t%9s\t\t%s\n", property.pid, property.tty_name, property.formed_utime, property.cmd);

            // ps -a
            // if(strcmp(property.tty_name, "?") && property.sid != property.pid && property.pid != ppid)
            // {
            //     printf("%5d\t\t%10s\t\t%9s\t\t%s\n", property.pid, property.tty_name, property.formed_utime, property.cmd);
            // }

            // ps -af
            // if(strcmp(property.tty_name, "?") && property.sid != property.pid && property.pid != ppid)
            // {
            //     printf("%-15s\t%5d\t%5d\t%d %5s %-5s\t%9s\t%s\n" , property.username , property.pid ,property.ppid , property.c , property.formed_STIME , property.tty_name , property.formed_utime, property.cmd);
            // }

            // ps -ef
            if (e == 1 && f == 0 && a == 0)//-e
            {
                printf("%4d\t\t%10s\t\t%9s\t\t%s\n", property.pid, property.tty_name, property.formed_utime, property.cmd);
            }
            else if (e == 0 && f == 0 && a == 0)//ps
            {
                if (!strcmp(property.tty_name, curtty))
                {
                    printf("%4d\t\t%10s\t\t%9s\t\t%s\n", property.pid, property.tty_name, property.formed_utime, property.cmd);
                }
            }
            else if (a == 1 && e == 0 && f == 0)//-a
            {
                if (strcmp(property.tty_name, "?") && property.sid != property.pid && property.pid != ppid)
                {
                    printf("%5d\t\t%10s\t\t%9s\t\t%s\n", property.pid, property.tty_name, property.formed_utime, property.cmd);
                }
            }
            else if (a == 1 && f == 1 && e == 0)//-af
            {
                if (strcmp(property.tty_name, "?") && property.sid != property.pid && property.pid != ppid)
                {
                    printf("%-15s\t%5d\t%5d\t%d %5s %-5s\t%9s\t%s\n", property.username, property.pid, property.ppid, property.c, property.formed_STIME, property.tty_name, property.formed_utime, property.cmd);
                }
            }
            else if (a == 0 && e == 1 && f == 1)//-ef
            {
                printf("%-15s\t%5d\t%5d\t%d %5s %-5s\t%9s\t%s\n", property.username, property.pid, property.ppid, property.c, property.formed_STIME, property.tty_name, property.formed_utime, property.cmd);
            }
            else
            {
                printf("Command not found !\n");
                break;
                
            }
        }
    }
    return 0;
}